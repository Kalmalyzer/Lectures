
#include <stdio.h>
#include <stdlib.h>
#include "UtanFelkoll.h"

void loadFile1(const char* name, void** buf, int* size)
{
	FILE* file = fopen(name, "rb");
	fseek(file, 0, SEEK_END);
	*size = ftell(file);
	fseek(file, 0, SEEK_SET);

	*buf = malloc(*size);

	fread(*buf, 1, *size, file);
	fclose(file);
}
