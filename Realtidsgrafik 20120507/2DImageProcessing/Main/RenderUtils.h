
#ifndef RENDERUTILS_H
#define RENDERUTILS_H

/*
   This file contains a bunch of helper functions.

   The main reason for drawPixel() and readPixel() is to remove the
    need for explicit bounds checking every time that a test program
	needs to index into an image. This makes it easier to test out and
	develop the algorithms themselves, at the cost of a a slight
	performance loss.

   The FIR filter functions apply a generic 1D or 2D FIR filter kernel.

   The IIR filter functions are specialized for a specific filter, namely
         y[n] = (1-t) * y[n-1] + t * x[n]
    which is a simplistic IIR lowpass filter (where t controls the cutoff
	frequency). The frequency characteristics of the filter are not
	particularly impressive, but it is cheap to compute in software and
	it looks nice when applied to graphics.
*/

class Image;
class FloatRGBColor;

FloatRGBColor readPixel(Image* output, int x, int y);

void drawPixel(Image* output, int x, int y, const FloatRGBColor& color);

void drawRectangle(Image* output, int x0, int y0, int x1, int y1, const FloatRGBColor& color);

void applyFIRFilterHorizontal(Image* input, Image* output, int numTaps, float* tapStrengths);
void applyFIRFilter(Image* input, Image* output, int numTapsX, int numTapsY, float* tapStrengths);

void applyIIRLowPassFilterRightward(Image* input, Image* output, float strength);
void applyIIRLowPassFilterLeftward(Image* input, Image* output, float strength);
void applyIIRLowPassFilterDownward(Image* input, Image* output, float strength);
void applyIIRLowPassFilterUpward(Image* input, Image* output, float strength);

void magnify2X(Image* input, Image* output, int centerX, int centerY);

#endif
