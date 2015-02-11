
#ifndef SCANCONVERSIONRENDERER_H
#define SCANCONVERSIONRENDERER_H

/*
   ScanConversionRenderer implements the logic for going through
    all lines in an image, and for each line asking "is there a
    span to be rendered on this line - and if so, where does it
    start and end?".

   Use it by subclassing ScanConversionRenderer and implementing
    computeSpanExtent().
 */

class FloatRGBColor;
class Image;

class ScanConversionRenderer
{
public:
	void render(Image* output, const FloatRGBColor& color);

protected:
	virtual bool computeSpanExtent(int y, int& start, int& end) = 0;
};

#endif
