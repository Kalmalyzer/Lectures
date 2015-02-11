
#include "Datatypes.h"

// Brute force CPU implementation which calculates signal strengths
//
// It iterates through all transmitter/receiver combinations and, for each receiver, records the
// highest found signal strength

void calculateCoverageCpu0(const PositionList& transmitters,
				 const PositionList& receivers,
				 CoverageList& coverages)
{
	coverages.clear();

	// Iterate through all transmitters

	for (PositionList::const_iterator transmitter = transmitters.begin();
		transmitter != transmitters.end();
		++transmitter)
	{
		// Count number of receivers within range

		uint coverageCount = 0;

		// Iterate through all receivers
	      
		for (PositionList::const_iterator receiver = receivers.begin();
			receiver != receivers.end();
			++receiver)
		{
			if (withinRange(*transmitter, *receiver))
				coverageCount++;
		}

      coverages.push_back(coverageCount);
    }
}
