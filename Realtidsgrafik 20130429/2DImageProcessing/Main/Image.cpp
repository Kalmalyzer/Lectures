#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>

#include "Types.h"
#include "Assert.h"
#include "Image.h"
#include "FloatRGBColor.h"

Image::Image(int width, int height)
	: m_width(width)
	, m_height(height)
	, m_pixels(new FloatRGBColor[width * height])
{
}

Image::~Image()
{
	delete [] m_pixels;
}


Image* loadBmp(const char* name)
{
	struct BmpHeader
	{
		u16 id;
		char pad[0x10];
		u16 width;
		char pad2[2];
		u16 height;
		char pad3[30];
	} bmpHeader;

	FILE* f = fopen(name, "rb");

	fread(&bmpHeader, 1, sizeof(bmpHeader), f);

	uint numPixels = bmpHeader.width * bmpHeader.height;
	u8 *tempBuf = new u8[numPixels * 3];

	fread(tempBuf, 1, numPixels * 3, f);
	fclose(f);

	Image* image = new Image(bmpHeader.width, bmpHeader.height);

	for (uint y = 0; y < bmpHeader.height; y++)
		for (uint x = 0; x < bmpHeader.width; x++)
		{
			uint sourceOffset = (bmpHeader.height - 1 - y) * bmpHeader.width + x;
			uint destOffset = y * bmpHeader.width + x;

			FloatRGBColor& destPixel = image->m_pixels[destOffset];

			destPixel.r = tempBuf[sourceOffset * 3 + 2];
			destPixel.g = tempBuf[sourceOffset * 3 + 1];
			destPixel.b = tempBuf[sourceOffset * 3 + 0];
		}

	delete [] tempBuf;

	return image;
}

void copy(Image* source, Image* dest)
{
	ASSERT(source->m_width == dest->m_width && source->m_height == dest->m_height);

	memcpy(dest->m_pixels, source->m_pixels, dest->m_width * dest->m_height * sizeof(FloatRGBColor));
}
