
// "Smart" CUDA implementation which computes signal strengths
//
// First, all transmitters are sorted into buckets
// Then, all receivers are sorted into buckets
// Then, receivers only compute signal strength against transmitters in nearby buckets
//
// This multi-step algorithm makes the signal strength computation scale much
//  better to high number of transmitters/receivers


///////////////////////////////////////////////////////////////////////////////////////////////
//
// Given a set of positions, compute how many of these will land in the respective bucket
//


static __global__ void buildBucketHistogramKernel(const Position* positions,
				     int numPositions,
				     unsigned int* histogram)
{
  int positionIndex = blockIdx.x * blockDim.x + threadIdx.x;

  if (positionIndex < numPositions)
    {

      const Position& position = positions[positionIndex];

      int bucketIndexX = (int) (position.x * BucketsPerAxis);
      int bucketIndexY = (int) (position.y * BucketsPerAxis);

      int bucketIndex = bucketIndexY * BucketsPerAxis + bucketIndexX;

      atomicInc(&histogram[bucketIndex], 0xffffffffU);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////
//
// Convert histogram into an array of (starting index, number of element) pairs

static __global__ void convertHistogramToBucketsKernel(const unsigned int* histogram,
					  int numElements,
					  Bucket* buckets)
{
  buckets[0].startIndex = 0;
  buckets[0].numElements = (int) histogram[0];
  for (int i = 0; i < numElements - 1; ++i)
    {
      buckets[i + 1].startIndex = buckets[i].startIndex + buckets[i].numElements;
      buckets[i + 1].numElements = (int) histogram[i + 1];
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////
//
// Copy out the bucket start indices to a new array

static __global__ void setupBucketWriteOffsetsKernel(const Bucket* buckets,
					int numElements,
					unsigned int* writeOffsets)
{
  for (int i = 0; i < numElements; ++i)
    writeOffsets[i] = (unsigned int) buckets[i].startIndex;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//
// Given the start-indices, copy 

static __global__ void remapPositionsKernel(const Position* inputPositions,
			       int numPositions,
			       Position* outputPositions,
			       unsigned int* writeOffsets)
{
  int inputIndex = blockIdx.x * blockDim.x + threadIdx.x;

  if (inputIndex < numPositions)
    {
      const Position& position = inputPositions[inputIndex];

      int bucketIndexX = (int) (position.x * BucketsPerAxis);
      int bucketIndexY = (int) (position.y * BucketsPerAxis);

      int bucketIndex = bucketIndexY * BucketsPerAxis + bucketIndexX;

      int outputIndex = (int) atomicInc(&writeOffsets[bucketIndex], 0xffffffffU);

      outputPositions[outputIndex] = position;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////
//
// Sort a set of positions into a set of buckets
//
// Given a set of input positions, these will be re-ordered such that
//  each range of elements in the output array belong to the same bucket.
// The list of buckets that is output describes where each such range begins
//  and ends in the re-ordered position array.

static void sortPositionsIntoBucketsCuda(CudaArray<Position>& cudaInputPositions,
			      CudaArray<Position>& cudaOutputPositions,
			      CudaArray<Bucket>& cudaOutputPositionBuckets)
{
  // Insert counting, phase 1:

  // Build histogram for positions
  
  CudaArray<unsigned int> bucketHistogram(cudaOutputPositionBuckets.size());

  int numThreads = std::min(cudaInputPositions.size(), 256);
  int numBlocks = (cudaInputPositions.size() + numThreads - 1) / numThreads;

  cudaMemset(bucketHistogram.cudaArray(), 0, bucketHistogram.size() *
	     sizeof(unsigned int));

  buildBucketHistogramKernel<<< numBlocks, numThreads >>>(cudaInputPositions.cudaArray(),
						    cudaInputPositions.size(),
						    bucketHistogram.cudaArray());
  CUDA_SAFE_CALL(cudaThreadSynchronize());
  CUT_CHECK_ERROR("Kernel execution failed");

  // Insert counting, phase 2:

  // Convert histogram to actual set of buckets

  convertHistogramToBucketsKernel<<< 1, 1 >>>(bucketHistogram.cudaArray(),
					bucketHistogram.size(),
					cudaOutputPositionBuckets.cudaArray());
  CUDA_SAFE_CALL(cudaThreadSynchronize());
  CUT_CHECK_ERROR("Kernel execution failed");

  // Copy bucket starting positions to a set of temporary write-offsets

  CudaArray<unsigned int> writeOffsets(cudaOutputPositionBuckets.size());

  setupBucketWriteOffsetsKernel<<< 1, 1 >>>(cudaOutputPositionBuckets.cudaArray(),
				      cudaOutputPositionBuckets.size(),
				      writeOffsets.cudaArray());
  CUDA_SAFE_CALL(cudaThreadSynchronize());
  CUT_CHECK_ERROR("Kernel execution failed");


  // Insert counting, phase 3:

  // Remap positions from temp to final array

  remapPositionsKernel<<< numBlocks, numThreads >>>(cudaInputPositions.cudaArray(),
					      cudaInputPositions.size(),
					      cudaOutputPositions.cudaArray(),
					      writeOffsets.cudaArray());
  CUDA_SAFE_CALL(cudaThreadSynchronize());
  CUT_CHECK_ERROR("Kernel execution failed");
}

///////////////////////////////////////////////////////////////////////////////////////////////
//
// Go through all transmitters in one bucket, find highest signal strength
// Return highest strength (or the old value, if that was higher)

static __device__ uint scanBucketKernel(const Position& transmitter, const Position* receivers, int numReceivers, uint coverage)
{
	for (int receiverIndex = 0; receiverIndex < numReceivers; ++receiverIndex)
    {
		const Position& receiver = receivers[receiverIndex];

		if (withinRange(transmitter, receiver))
			++coverage;
    }

	return coverage;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//
// Calculate signal strength for all receivers

static __global__ void calculateCoverageKernel2(const Position* transmitters,
						     const Bucket* transmitterBuckets,
						     const Position* receivers,
						     const Bucket* receiverBuckets,
						     uint* coverages)
{
	// Determine which bucket the current grid block is processing

	int transmitterBucketIndexX = blockIdx.x;
	int transmitterBucketIndexY = blockIdx.y;

	int transmitterBucketIndex = transmitterBucketIndexY * BucketsPerAxis + transmitterBucketIndexX;

	const Bucket& transmitterBucket = transmitterBuckets[transmitterBucketIndex];

	int transmitterStartIndex = transmitterBucket.startIndex;
	int numtransmitters = transmitterBucket.numElements;

	// Distribute available transmitters over the set of available threads

	for (int transmitterIndex = threadIdx.x; transmitterIndex < numtransmitters; transmitterIndex += blockDim.x)
	{
		// Locate current transmitter within the current bucket

		const Position& transmitter = transmitters[transmitterStartIndex + transmitterIndex];
		uint& finalCoverage = coverages[transmitterStartIndex + transmitterIndex];

		uint coverage = 0;

		// Scan all buckets in the 3x3 region enclosing the transmitter's bucket index
      
		for (int receiverBucketIndexY = transmitterBucketIndexY - 1; receiverBucketIndexY < transmitterBucketIndexY + 2; ++receiverBucketIndexY)
			for (int receiverBucketIndexX = transmitterBucketIndexX - 1; receiverBucketIndexX < transmitterBucketIndexX + 2; ++receiverBucketIndexX)
			{
				// Only process bucket if its index is within [0, BucketsPerAxis - 1] along each axis

				if (receiverBucketIndexX >= 0 && receiverBucketIndexX < BucketsPerAxis
					&& receiverBucketIndexY >= 0 && receiverBucketIndexY < BucketsPerAxis)
				{
					// Compute coverage for all receivers in current bucket

					int receiverBucketIndex = receiverBucketIndexY * BucketsPerAxis + receiverBucketIndexX;
					int receiverStartIndex = receiverBuckets[receiverBucketIndex].startIndex;
					int numReceivers = receiverBuckets[receiverBucketIndex].numElements;
					coverage = scanBucketKernel(transmitter, &receivers[receiverStartIndex], numReceivers, coverage);
				}
			}

		// Store out the highest signal strength found for the transmitter

		finalCoverage = coverage;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void calculateCoverageCuda2(const PositionList& cpuTransmitters,
				  const PositionList& cpuReceivers,
				  CoverageList& cpuCoverages)
{
	int numBuckets = BucketsPerAxis * BucketsPerAxis;
	// Copy input positions to device memory
	CudaArray<Position> cudaTempTransmitters(cpuTransmitters.size());
	cudaTempTransmitters.copyToCuda(&(*cpuTransmitters.begin()));

	CudaArray<Position> cudaTempReceivers(cpuReceivers.size());
	cudaTempReceivers.copyToCuda(&(*cpuReceivers.begin()));
	// Allocate device memory for sorted arrays

	CudaArray<Position> cudaTransmitters(cpuTransmitters.size());
	CudaArray<Bucket> cudaTransmitterBuckets(numBuckets);

	CudaArray<Position> cudaReceivers(cpuReceivers.size());
	CudaArray<Bucket> cudaReceiverBuckets(numBuckets);

	// Sort transmitters and receivers into buckets
	
	sortPositionsIntoBucketsCuda(cudaTempTransmitters, cudaTransmitters, cudaTransmitterBuckets);
	sortPositionsIntoBucketsCuda(cudaTempReceivers, cudaReceivers, cudaReceiverBuckets);
	
	// Perform signal strength computation
	CudaArray<uint> cudaCoverages(cpuTransmitters.size());
	
	int numThreads = 256;
	dim3 grid = dim3(BucketsPerAxis, BucketsPerAxis);

	calculateCoverageKernel2<<< grid, numThreads >>>(cudaTransmitters.cudaArray(), cudaTransmitterBuckets.cudaArray(),
		cudaReceivers.cudaArray(), cudaReceiverBuckets.cudaArray(), cudaCoverages.cudaArray());
	CUDA_SAFE_CALL(cudaThreadSynchronize());
	CUT_CHECK_ERROR("Kernel execution failed");

	// Copy results back to host memory

	cpuCoverages.resize(cudaCoverages.size());
	cudaCoverages.copyFromCuda(&(*cpuCoverages.begin()));
}
