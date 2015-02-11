
#ifndef ASSERT_H
#define ASSERT_H

#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#include <cstdlib>
#include <windows.h>

#define ASSERT(condition) \
	do \
	{ \
		if (!condition) \
		{ \
			char buf[1024]; \
			sprintf(buf, "%s(%d): Assertion failed: %s\n", __FILE__, __LINE__, #condition); \
			puts(buf); \
			OutputDebugStringA(buf); \
			if (IsDebuggerPresent()) \
				__debugbreak(); \
			else \
				exit(0); \
		} \
	} while(false);

#endif