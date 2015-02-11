
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////////////////

int* generateRandomData()
{
	int* data = (int*) malloc(40000);

	for (int i = 0; i < 10000; i++)
	{
		data[i] = rand();
	}

	return data;
}

//////////////////////////////////////////////////////////////////////////////////////////////

void filterKernel(int* data)
{
	int avg = 0;

	for (int i = 0; i < 10000; i++)
		avg += data[i];

	avg /= 10000;

	for (int i = 0; i < 10000; i++)
		data[i] -= avg;

	for (int i = 0; i < 9999; i++)
		data[i] -= data[i + 1];
}

//////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
	int* data = generateRandomData();
	filterKernel(data);
	free(data);

	return 0;
}