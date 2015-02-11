
#include "CudaArray.h"

// Brute force CUDA implementation
//
// It iterates through all transmitter/receiver combinations and, for each receiver, records the
// highest found signal strength 

///////////////////////////////////////////////////////////////////////////////////////////////
// Compute maximum signal strength for a set of transmitters/receivers
// 
// Each thread evaluates one receiver against all transmitters, and records the highest found
//  strength into the signalStrengths[] array


static __global__ void calculateCoveragesKernel1(const Position* transmitters,
						      uint numTransmitters,
						      const Position* receivers,
						      uint numReceivers,
						      uint* coverages)
{
	// Locate the receiver which we should be working on

	uint transmitterIndex = blockIdx.x * blockDim.x + threadIdx.x;

	if (transmitterIndex < numTransmitters)
	{
		const Position& transmitter = transmitters[transmitterIndex];
		uint& finalCoverage = coverages[transmitterIndex];

		// Iterate through all transmitters
      
		uint coverage = 0;

		for (uint receiverIndex = 0; receiverIndex < numReceivers; ++receiverIndex)
		{
			const Position& receiver = receivers[receiverIndex];

			if (withinRange(transmitter, receiver))
				coverage++;

		}

		// Store final coverage for this transmitter

		finalCoverage = coverage;
    }
} 

///////////////////////////////////////////////////////////////////////////////////////////////
  
void calculateCoverageCuda1(const PositionList& cpuTransmitters,
				 const PositionList& cpuReceivers,
				 CoverageList& cpuCoverages)
{
	// Allocate device memory for input and output arrays

	CudaArray<Position> cudaTransmitters(cpuTransmitters.size());
	CudaArray<Position> cudaReceivers(cpuReceivers.size());
	CudaArray<uint> cudaCoverages(cpuTransmitters.size());

	// Copy transmitter & receiver arrays to device memory

	cudaTransmitters.copyToCuda(&(*cpuTransmitters.begin()));
	cudaReceivers.copyToCuda(&(*cpuReceivers.begin()));

	// Perform signal strength computation

	uint numThreads = std::min(cudaTransmitters.size(), 256);
	uint numBlocks = (cudaTransmitters.size() + numThreads - 1) / numThreads;

	calculateCoveragesKernel1<<< numBlocks, numThreads >>>(cudaTransmitters.cudaArray(), cudaTransmitters.size(),
		cudaReceivers.cudaArray(), cudaReceivers.size(), cudaCoverages.cudaArray());

	CUDA_SAFE_CALL(cudaThreadSynchronize());
	CUT_CHECK_ERROR("Kernel execution failed");

	// Copy results back to host memory

	cpuCoverages.resize(cudaCoverages.size());
	cudaCoverages.copyFromCuda(&(*cpuCoverages.begin())); 
}
