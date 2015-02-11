
#include <stdio.h>

#include "../FloatTypes/FloatTypes.h"

int main(void)
{
	SinglePrecisionFloat seconds(0.0);
	SinglePrecisionFloat step(1.0 / 60.0);

	for (int i = 0; i < 100000000; i++)
	{
		if (i % 10000 == 0)
			printf("%d %f %s\n", i, seconds.getValue(), seconds.getBinaryString().c_str());

		seconds = seconds + step;
	}

	return 0;
}
