
#ifndef FloatRGBColor_h
#define FloatRGBColor_h

/*
   FloatRGBColor represents a triplet of color channels.
   The color channels are declared as floats instead of ints to make it simple to
    use for experimentation, and to make the class useful for holding per-channel
    scale factors, and the likes, without having to worry about losing precision
    at every computational step.

   A FloatRGBColor can often be used like a 3D vector. Many of the math operations
    you'd expect to have for a 3D vector are also available for the FloatRGBColor type.
*/

#include "Types.h"

#include <cmath>
#include <algorithm>

class FloatRGBColor
{
public:
	float r, g, b;

	FloatRGBColor();

	explicit FloatRGBColor(float r0, float g0, float b0);

	friend FloatRGBColor operator -(const FloatRGBColor& color);

	FloatRGBColor operator +(const FloatRGBColor& color) const;
	FloatRGBColor operator -(const FloatRGBColor& color) const;

	FloatRGBColor operator *(float f) const;

	FloatRGBColor operator +=(const FloatRGBColor& color);
	FloatRGBColor operator -=(const FloatRGBColor& color);

	FloatRGBColor operator *=(float f);

};

FloatRGBColor operator -(const FloatRGBColor& color);
FloatRGBColor operator *(float f, const FloatRGBColor& color);

float dot(const FloatRGBColor& color0, const FloatRGBColor& color1);

float length(const FloatRGBColor& color);

FloatRGBColor normalize(const FloatRGBColor& color);

FloatRGBColor cross(const FloatRGBColor& color0, const FloatRGBColor& color1);

FloatRGBColor min(const FloatRGBColor& color0, const FloatRGBColor& color1);
FloatRGBColor max(const FloatRGBColor& color0, const FloatRGBColor& color1);
FloatRGBColor clamp(const FloatRGBColor& color, const FloatRGBColor& min, const FloatRGBColor& max);

FloatRGBColor lerp(const FloatRGBColor& color0, const FloatRGBColor& color1, float t);


#endif
