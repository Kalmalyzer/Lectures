
#include <stdio.h>

#include "../FloatTypes/FloatTypes.h"

int main(void)
{
	int ticks = 0;
	int step = 1;
	SinglePrecisionFloat ticksPerSecond(1.0 / 60.0);

	for (int i = 0; i < 100000000; i++)
	{
		SinglePrecisionFloat seconds = SinglePrecisionFloat(ticks) * ticksPerSecond;

		if (i % 10000 == 0)
			printf("%d %f %s\n", i, seconds.getValue(), seconds.getBinaryString().c_str());

		ticks = ticks + 1;
	}

	return 0;
}
