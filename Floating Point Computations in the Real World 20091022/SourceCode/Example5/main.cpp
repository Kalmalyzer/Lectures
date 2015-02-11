
#include <stdio.h>

#include "../FloatTypes/FloatTypes.h"

int main(void)
{
	for (int i = 1; i < 1000; i++)
	{
		SinglePrecisionFloat one(1.0);
		SinglePrecisionFloat iFloat(i);
		SinglePrecisionFloat reciprocal	= one / iFloat;
		SinglePrecisionFloat ratio = iFloat * reciprocal;

		printf("%d %1.10f %s\n", i, ratio.getValue(), ratio.getBinaryString().c_str());
	}

	return 0;
}
