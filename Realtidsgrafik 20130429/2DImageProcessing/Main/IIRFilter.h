
#ifndef IIRFILTER_H
#define IIRFILTER_H

class Image;
class FloatRGBColor;

void applyIIRLowPassFilterRightward(Image* input, Image* output, float strength);
void applyIIRLowPassFilterLeftward(Image* input, Image* output, float strength);
void applyIIRLowPassFilterDownward(Image* input, Image* output, float strength);
void applyIIRLowPassFilterUpward(Image* input, Image* output, float strength);

#endif
