
#ifndef _Datatypes_h_
#define _Datatypes_h_


#include <vector>

typedef unsigned int uint;



enum { BucketsPerAxis = 16 };         // The bucket sort should subdivide the whole domain into
                                      // BucketsPerAxis x BucketsPerAxis number of buckets

struct Position
{
  float x, y;
};

typedef std::vector<Position> PositionList; // Set of positions (either transmitters or receivers)

typedef std::vector<uint> CoverageList; // Set of coverage indices

typedef PositionList PositionListGrid[BucketsPerAxis][BucketsPerAxis];



struct Bucket
{
  uint startIndex;         // Start of bucket within array
  uint numElements;        // Number of elements in bucket
};



static __inline__ __host__ __device__ bool withinRange(const Position& transmitter, const Position& receiver)
{
	const float maxTransceiverDistance = 0.01f;

	float dx = receiver.x - transmitter.x;
	float dy = receiver.y - transmitter.y;
	float sqrDist = dx * dx + dy * dy;
	
	return sqrt(sqrDist) < maxTransceiverDistance;
}

static __inline__ __host__ __device__ void bucketize(const Position& position, uint& bucketX, uint& bucketY)
{
	bucketX = (int) (position.x * BucketsPerAxis);
	bucketY = (int) (position.y * BucketsPerAxis);
}

#endif // _Datatypes_h_  