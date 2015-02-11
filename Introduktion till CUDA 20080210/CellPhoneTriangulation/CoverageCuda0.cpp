
#include "CudaArray.h"

// Brute force CUDA implementation
//
// It iterates through all transmitter/receiver combinations and, for each receiver, records the
// highest found signal strength 

///////////////////////////////////////////////////////////////////////////////////////////////
// Compute maximum signal strength for a set of transmitters/receivers
// 

static __global__ void calculateCoveragesKernel0(const Position* transmitters,
						      uint numTransmitters,
						      const Position* receivers,
						      uint numReceivers,
						      uint* coverages)
{
	// Iterate through all transmitters
	for (uint transmitterIndex = 0; transmitterIndex < numTransmitters; ++transmitterIndex)
	{
		const Position& transmitter = transmitters[transmitterIndex];
		uint& finalCoverage = coverages[transmitterIndex];

		// Iterate through all receivers
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
  
void calculateCoverageCuda0(const PositionList& cpuTransmitters,
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

	calculateCoveragesKernel0<<< 1, 1 >>>(cudaTransmitters.cudaArray(), cudaTransmitters.size(),
		cudaReceivers.cudaArray(), cudaReceivers.size(), cudaCoverages.cudaArray());

	CUDA_SAFE_CALL(cudaThreadSynchronize());
	CUT_CHECK_ERROR("Kernel execution failed");

	// Copy results back to host memory

	cpuCoverages.resize(cudaCoverages.size());
	cudaCoverages.copyFromCuda(&(*cpuCoverages.begin())); 
}
