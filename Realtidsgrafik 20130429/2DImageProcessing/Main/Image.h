
#ifndef IMAGE_H
#define IMAGE_H

/*
   Image represents a 2D image. The pixels themselves are stored in a linear array.
   You index a pixel at location (x,y) in the image by accessing m_pixels[y * m_width + x].
 */

class FloatRGBColor;

class Image
{
public:
	int m_width;
	int m_height;
	FloatRGBColor* m_pixels;

	explicit Image(int width, int height);
	~Image();
};

Image* loadBmp(const char* fileName);

void copy(Image* source, Image* dest);

#endif
