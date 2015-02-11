
#include <stdio.h>

#include "../FloatTypes/FloatTypes.h"

int main(void)
{
	SinglePrecisionFloat f(0.0);
	SinglePrecisionFloat step(1.0);

	for (int i = 0; i < 100000000; i++)
	{
		if (i % 10000 == 0)
			printf("%d %f %s\n", i, f.getValue(), f.getBinaryString().c_str());

		f = f + step;
	}

	return 0;
}
