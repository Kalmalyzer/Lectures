
#include <stdio.h>

#include "../FloatTypes/FloatTypes.h"

int main(void)
{
	int x = 0;
	int step = 1;

	for (int i = 0; i < 100000000; i++)
	{
		if (i % 10000 == 0)
			printf("%d %d\n", i, x);

		x = x + step;
	}

	return 0;
}
