
#include <stdio.h>

#include "UtanFelkoll.h"
#include "MedFelkoll.h"
#include "MedScopeObjekt.h"

int main(void)
{
	void* buf;
	int size;
	loadFile1("test.txt", &buf, &size);
	loadFile2("test.txt", &buf, &size);
	loadFile3("test.txt", &buf, &size);

	return 0;
}