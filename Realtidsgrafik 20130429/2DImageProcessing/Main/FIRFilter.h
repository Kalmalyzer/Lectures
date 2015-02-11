
#ifndef FIRFILTER_H
#define FIRFILTER_H

class Image;
class FloatRGBColor;

void applyFIRFilterHorizontal(Image* input, Image* output, int numTaps, float* tapStrengths);
void applyFIRFilter(Image* input, Image* output, int numTapsX, int numTapsY, float* tapStrengths);

#endif
