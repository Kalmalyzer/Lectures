
#include <stdio.h>

#include <cutil.h>

#include "Datatypes.h"

#include "CoverageCpu0.cpp"
#include "CoverageCpu1.cpp"
#include "CoverageCpu2.cpp"
#include "CoverageCuda0.cpp"
#include "CoverageCuda1.cpp"
#include "CoverageCuda2.cpp"

///////////////////////////////////////////////////////////////////////////////////////////////
//
// Generate initial positions for transmitters/receivers
//
// By default, their positions are randomly chosen within the [(0,0) .. (0.999,0.999)] 2D interval

PositionList generateRandomPositions(int numPositions)
{
	PositionList positions;

	for (int i = 0; i < numPositions; ++i)
	{
		Position position;
		position.x = ((float) rand() * 0.999f) / RAND_MAX;
		position.y = ((float) rand() * 0.999f) / RAND_MAX;
		positions.push_back(position);
	}

	return positions;
}

PositionList createTransmitters(int numTransmitters)
{
	return generateRandomPositions(numTransmitters);
}

PositionList createReceivers(int numReceivers)
{
	return generateRandomPositions(numReceivers);
}

///////////////////////////////////////////////////////////////////////////////////////////////
//
// Given a coverage list, compute various statistics for the list

void calcCoverageStatistics(const CoverageList& coverages,
	int* transmitterCoverageStats)
{
	for (uint i = 0; i < 4; i++)
	transmitterCoverageStats[i] = 0;

	for (CoverageList::const_iterator coverage = coverages.begin();
	   coverage != coverages.end();
	   ++coverage)
	{
		if (*coverage < 3)
			transmitterCoverageStats[*coverage]++;
		else
			transmitterCoverageStats[3]++;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		printf("Usage: CellPhoneCoverage <num transmitters> <num receivers> <method [0, 1, 2]>\n");
		return 1;
	}

	int numTransmitters = atoi(argv[1]);
	int numReceivers = atoi(argv[2]);

	int method = atoi(argv[3]); 

	CUT_DEVICE_INIT(argc, argv);

	printf("\n");

	// Initialize CUDA context by performing some arbitrary CUDA call
	//  (makes timing figures more accurate)
	CudaArray<int> dummy(10);

	// Generate transmitters & receivers

	PositionList cpuTransmitters = createTransmitters(numTransmitters);
	PositionList cpuReceivers = createReceivers(numReceivers);

	// Calculate coverages

	CoverageList cpuCoverages;

	uint timerId;
	CUDA_SAFE_CALL(cutCreateTimer(&timerId));
	CUDA_SAFE_CALL(cutStartTimer(timerId));

	switch (method)
	{
	case 0:
		printf("Performing brute-force CPU computation\n");
		calculateCoverageCpu0(cpuTransmitters, cpuReceivers, cpuCoverages);
		break;
	case 1:
		printf("Performing bucketized (STL) CPU computation\n");
		calculateCoverageCpu1(cpuTransmitters, cpuReceivers, cpuCoverages);
		break;
	case 2:
		printf("Performing bucketized (raw) CPU computation\n");
		calculateCoverageCpu2(cpuTransmitters, cpuReceivers, cpuCoverages);
		break;
	case 3:
		printf("Performing single-threaded CUDA computation\n");
		calculateCoverageCuda0(cpuTransmitters, cpuReceivers, cpuCoverages);
		break;
	case 4:
		printf("Performing brute-force CUDA computation\n");
		calculateCoverageCuda1(cpuTransmitters, cpuReceivers, cpuCoverages);
		break;
	case 5:
		printf("Performing bucketized CUDA computation\n");
		calculateCoverageCuda2(cpuTransmitters, cpuReceivers, cpuCoverages);
		break;
	}

	float computationTime = cutGetTimerValue(timerId);

	CUDA_SAFE_CALL(cutDeleteTimer(timerId));

	// Generate statistics

	int transmitterCoverageStats[4];

	calcCoverageStatistics(cpuCoverages, transmitterCoverageStats);

	printf("%d transmitters, %d receivers\n", numTransmitters, numReceivers);

	printf("Time taken: %f ms\n", computationTime);

	printf("Bucket counts:\n");
	for (uint i = 0; i < 4; i++)
		printf("%d: %d\n", i, transmitterCoverageStats[i]);

	return 0;
}
