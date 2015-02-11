
#include <stdio.h>
#include <stdlib.h>

#include "ScopedFile.h"

bool loadFile3(const char* name, void** buf, int* size)
{
	ScopedFile file(name, "rb");

	if (!file.isOpen())
		return false;

	if (fseek(file.get(), 0, SEEK_END) == -1)
		return false;

	*size = ftell(file.get());
	if (*size == -1)
		return false;

	if (fseek(file.get(), 0, SEEK_SET) == -1)
		return false;

	*buf = malloc(*size);
	if (!buf)
		return false;

	if (fread(*buf, 1, *size, file.get()) != *size)
	{
		free(*buf);
		return false;
	}
		
	return true;
}
