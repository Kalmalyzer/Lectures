
#include "Datatypes.h"

void bucketize(const PositionList& positions, PositionListGrid buckets)
{
	for (PositionList::const_iterator position = positions.begin(); position != positions.end(); ++position)
	{
		uint bucketX, bucketY;
		bucketize(*position, bucketX, bucketY);

		buckets[bucketY][bucketX].push_back(*position);
	}
}

// Bucketized CPU implementation
//
// It stuffs transmitters & receivers into buckets, and then only does coverage tests between
//  transmitters and receivers which are reasonably close to each other

void calculateCoverageCpu1(const PositionList& transmitters,
				 const PositionList& receivers,
				 CoverageList& coverages)
{
	// Sort transmitters & receivers into a pair of 2d grids

	PositionListGrid transmitterBuckets;
	PositionListGrid receiverBuckets;

	bucketize(transmitters, transmitterBuckets);
	bucketize(receivers, receiverBuckets);


	coverages.clear();

	// Iterate through all transmitters
	for (uint transmitterBucketY = 0; transmitterBucketY < BucketsPerAxis; ++transmitterBucketY)
		for (uint transmitterBucketX = 0; transmitterBucketX < BucketsPerAxis; ++transmitterBucketX)
			for (PositionList::const_iterator transmitter = transmitterBuckets[transmitterBucketY][transmitterBucketX].begin();
				transmitter != transmitterBuckets[transmitterBucketY][transmitterBucketX].end();
				++transmitter)
			{
				// Count number of receivers within range

				uint coverageCount = 0;

				// Iterate through receivers in the neighbourhood

				uint receiverBucketMinX = std::max(1U, transmitterBucketX) - 1;
				uint receiverBucketMaxX = std::min((uint) BucketsPerAxis, transmitterBucketX + 2);
				uint receiverBucketMinY = std::max(1U, transmitterBucketY) - 1;
				uint receiverBucketMaxY = std::min((uint) BucketsPerAxis, transmitterBucketY + 2);

				for (uint receiverBucketY = receiverBucketMinY; receiverBucketY < receiverBucketMaxY; ++receiverBucketY)
					for (uint receiverBucketX = receiverBucketMinX; receiverBucketX < receiverBucketMaxX; ++receiverBucketX)
						for (PositionList::const_iterator receiver = receiverBuckets[receiverBucketY][receiverBucketX].begin();
							receiver != receiverBuckets[receiverBucketY][receiverBucketX].end();
							++receiver)
						{
							if (withinRange(*transmitter, *receiver))
								coverageCount++;
						}

				coverages.push_back(coverageCount);
			}
}
