
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


static void buildBucketHistogram(const Position* positions,
				     uint numPositions,
				     unsigned int* histogram)
{
	for (uint positionIndex = 0; positionIndex < numPositions; ++positionIndex)
	{

		const Position& position = positions[positionIndex];

		uint bucketIndexX = (uint) (position.x * BucketsPerAxis);
		uint bucketIndexY = (uint) (position.y * BucketsPerAxis);

		uint bucketIndex = bucketIndexY * BucketsPerAxis + bucketIndexX;

		histogram[bucketIndex]++;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
//
// Convert histogram into an array of (starting index, number of element) pairs

static void convertHistogramToBuckets(const unsigned int* histogram,
					  uint numElements,
					  Bucket* buckets)
{
	buckets[0].startIndex = 0;
	buckets[0].numElements = histogram[0];
	for (uint i = 0; i < numElements - 1; ++i)
	{
		buckets[i + 1].startIndex = buckets[i].startIndex + buckets[i].numElements;
		buckets[i + 1].numElements = histogram[i + 1];
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
//
// Copy out the bucket start indices to a new array

static void setupBucketWriteOffsets(const Bucket* buckets,
					uint numElements,
					unsigned int* writeOffsets)
{
	for (uint i = 0; i < numElements; ++i)
		writeOffsets[i] = buckets[i].startIndex;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//
// Given the start-indices, copy 

static void remapPositions(const Position* inputPositions,
			       uint numPositions,
			       Position* outputPositions,
			       uint* writeOffsets)
{
	for (uint inputIndex = 0; inputIndex < numPositions; ++inputIndex)
	{
		const Position& position = inputPositions[inputIndex];

		uint bucketIndexX = (uint) (position.x * BucketsPerAxis);
		uint bucketIndexY = (uint) (position.y * BucketsPerAxis);

		uint bucketIndex = bucketIndexY * BucketsPerAxis + bucketIndexX;

		uint outputIndex = writeOffsets[bucketIndex]++;

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

static void sortPositionsIntoBuckets(std::vector<Position>& cudaInputPositions,
									 std::vector<Position>& cudaOutputPositions,
									 std::vector<Bucket>& cudaOutputPositionBuckets)
{
	// Insert counting, phase 1:

	// Build histogram for positions
  
	std::vector<uint> bucketHistogram;
	bucketHistogram.resize(cudaOutputPositionBuckets.size());

	for (uint i = 0; i < bucketHistogram.size(); ++i)
		bucketHistogram[i] = 0;

	buildBucketHistogram(&cudaInputPositions[0], cudaInputPositions.size(), &bucketHistogram[0]);
	CUDA_SAFE_CALL(cudaThreadSynchronize());
	CUT_CHECK_ERROR("Kernel execution failed");

	// Insert counting, phase 2:

	// Convert histogram to actual set of buckets

	convertHistogramToBuckets(&bucketHistogram[0], bucketHistogram.size(), &cudaOutputPositionBuckets[0]);

	// Copy bucket starting positions to a set of temporary write-offsets

	std::vector<uint> writeOffsets;
	writeOffsets.resize(cudaOutputPositionBuckets.size());

	setupBucketWriteOffsets(&cudaOutputPositionBuckets[0],
				      cudaOutputPositionBuckets.size(),
				      &writeOffsets[0]);

	// Insert counting, phase 3:

	// Remap positions from temp to final array

	remapPositions(&cudaInputPositions[0], cudaInputPositions.size(), &cudaOutputPositions[0], &writeOffsets[0]);
}

///////////////////////////////////////////////////////////////////////////////////////////////
//
// Go through all transmitters in one bucket, find highest signal strength
// Return highest strength (or the old value, if that was higher)

static uint scanBucket(const Position& transmitter, const Position* receivers, int numReceivers, uint coverage)
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

static void calculateCoverageCpu2Bucket(const Position* transmitters,
						     const Bucket* transmitterBuckets,
						     const Position* receivers,
						     const Bucket* receiverBuckets,
						     uint* coverages,
							 uint transmitterBucketIndexX,
							 uint transmitterBucketIndexY)
{
	// Determine which bucket the current grid block is processing

	uint transmitterBucketIndex = transmitterBucketIndexY * BucketsPerAxis + transmitterBucketIndexX;

	const Bucket& transmitterBucket = transmitterBuckets[transmitterBucketIndex];

	uint transmitterStartIndex = transmitterBucket.startIndex;
	uint numTransmitters = transmitterBucket.numElements;

	// Distribute available transmitters over the set of available threads

	for (uint transmitterIndex = 0; transmitterIndex < numTransmitters; transmitterIndex++)
	{
		// Locate current transmitter within the current bucket

		const Position& transmitter = transmitters[transmitterStartIndex + transmitterIndex];
		uint& finalCoverage = coverages[transmitterStartIndex + transmitterIndex];

		uint coverage = 0;

		// Scan all buckets in the 3x3 region enclosing the transmitter's bucket index
      
		for (int receiverBucketIndexY = (int) transmitterBucketIndexY - 1; receiverBucketIndexY < (int) transmitterBucketIndexY + 2; ++receiverBucketIndexY)
			for (int receiverBucketIndexX = (int) transmitterBucketIndexX - 1; receiverBucketIndexX < (int) transmitterBucketIndexX + 2; ++receiverBucketIndexX)
			{
				// Only process bucket if its index is within [0, BucketsPerAxis - 1] along each axis

				if (receiverBucketIndexX >= 0 && receiverBucketIndexX < BucketsPerAxis
					&& receiverBucketIndexY >= 0 && receiverBucketIndexY < BucketsPerAxis)
				{
					// Compute coverage for all receivers in current bucket

					uint receiverBucketIndex = receiverBucketIndexY * BucketsPerAxis + receiverBucketIndexX;
					uint receiverStartIndex = receiverBuckets[receiverBucketIndex].startIndex;
					uint numReceivers = receiverBuckets[receiverBucketIndex].numElements;
					coverage = scanBucket(transmitter, &receivers[receiverStartIndex], numReceivers, coverage);
				}
			}

		// Store out the highest signal strength found for the transmitter

		finalCoverage = coverage;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

void calculateCoverageCpu2(const PositionList& cpuTransmitters,
				  const PositionList& cpuReceivers,
				  CoverageList& cpuCoverages)
{
	int numBuckets = BucketsPerAxis * BucketsPerAxis;

	// Copy input positions to device memory
	std::vector<Position> cudaTempTransmitters = cpuTransmitters;

	std::vector<Position> cudaTempReceivers = cpuReceivers;

	// Allocate device memory for sorted arrays

	std::vector<Position> cudaTransmitters;
	cudaTransmitters.resize(cpuTransmitters.size());
	std::vector<Bucket> cudaTransmitterBuckets;
	cudaTransmitterBuckets.resize(numBuckets);

	std::vector<Position> cudaReceivers;
	cudaReceivers.resize(cpuReceivers.size());
	std::vector<Bucket> cudaReceiverBuckets;
	cudaReceiverBuckets.resize(numBuckets);

	// Sort transmitters and receivers into buckets
	
	sortPositionsIntoBuckets(cudaTempTransmitters, cudaTransmitters, cudaTransmitterBuckets);
	sortPositionsIntoBuckets(cudaTempReceivers, cudaReceivers, cudaReceiverBuckets);
	
	// Perform signal strength computation
	std::vector<uint> cudaCoverages;
	cudaCoverages.resize(cpuTransmitters.size());
	
	for (uint transmitterBucketIndexY = 0; transmitterBucketIndexY < BucketsPerAxis; ++transmitterBucketIndexY)
		for (uint transmitterBucketIndexX = 0; transmitterBucketIndexX < BucketsPerAxis; ++transmitterBucketIndexX)
			calculateCoverageCpu2Bucket(&cudaTransmitters[0], &cudaTransmitterBuckets[0],
				&cudaReceivers[0], &cudaReceiverBuckets[0], &cudaCoverages[0],
				transmitterBucketIndexX, transmitterBucketIndexY);

	// Copy results back to host memory

	cpuCoverages = cudaCoverages;
	
}  