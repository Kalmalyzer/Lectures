
#ifndef PERPIXELTESTRENDERER_H
#define PERPIXELTESTRENDERER_H

/*
   PerPixelTestRenderer implements the logic for going through
    all pixels in an image, asking "is this pixel inside the shape to render?"
    and if the answer is yes, then rendering that pixel with the
    desired color.

   Use it by subclassing and implementing the isInside() method.
 */

class FloatRGBColor;
class Image;

class PerPixelTestRenderer
{
public:
	void render(Image* output);

protected:
	virtual bool isInside(int x, int y) = 0;
	virtual FloatRGBColor getInsideColor() = 0;
};

#endif

