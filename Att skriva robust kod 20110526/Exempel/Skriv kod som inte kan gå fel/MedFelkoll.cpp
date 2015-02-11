

#include <stdio.h>
#include <stdlib.h>
#include "MedFelkoll.h"

bool loadFile2(const char* name, void** buf, int* size)
{
	FILE* file = fopen(name, "rb");
	if (fseek(file, 0, SEEK_END) == -1)
	{
		fclose(file);
		return false;
	}
	*size = ftell(file);
	if (*size < 0)
	{
		fclose(file);
		return false;
	}
	if (fseek(file, 0, SEEK_SET) < 0)
	{
		fclose(file);
		return false;
	}

	*buf = malloc(*size);
	if (!*buf)
	{
		fclose(file);
		return false;
	}

	if (fread(*buf, 1, *size, file) != *size)
	{
		fclose(file);
		return false;
	}

	fclose(file);
	return true;
}
