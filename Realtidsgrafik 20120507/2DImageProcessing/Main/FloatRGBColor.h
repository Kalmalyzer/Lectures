
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

	FloatRGBColor() { }

	explicit FloatRGBColor(float r0, float g0, float b0)
		: r(r0), g(g0), b(b0)
	{
	}

	friend FloatRGBColor operator -(const FloatRGBColor& color);

	FloatRGBColor operator +(const FloatRGBColor& color) const
	{
		return FloatRGBColor(r + color.r, g + color.g, b + color.b);
	}
	
	FloatRGBColor operator -(const FloatRGBColor& color) const
	{
		return *this + (-color);
	}

	FloatRGBColor operator *(float f) const
	{
		return FloatRGBColor(r * f, g * f, b * f);
	}

	FloatRGBColor operator +=(const FloatRGBColor& color)
	{
		return *this = *this + color;
	}

	FloatRGBColor operator -=(const FloatRGBColor& color)
	{
		return *this = *this - color;
	}

	FloatRGBColor operator *=(float f)
	{
		return *this = *this * f;
	}

};

inline FloatRGBColor operator -(const FloatRGBColor& color)
{
	return FloatRGBColor(-color.r, -color.g, -color.b);
}

inline float dot(const FloatRGBColor& color0, const FloatRGBColor& color1)
{
	return color0.r * color1.r + color0.g * color1.g + color0.b * color1.b;
}

inline float length(const FloatRGBColor& color)
{
	return sqrt(dot(color, color));
}

inline FloatRGBColor operator *(float f, const FloatRGBColor& color)
{
	return color * f;
}

inline FloatRGBColor normalize(const FloatRGBColor& color)
{
	return (1.f / length(color)) * color;
}

inline FloatRGBColor cross(const FloatRGBColor& color0, const FloatRGBColor& color1)
{
	return FloatRGBColor(color0.g * color1.b - color0.b * color1.g,
				color0.b * color1.r - color0.r * color1.b,
				color0.r * color1.g - color0.g * color1.r);
}

inline FloatRGBColor max(const FloatRGBColor& color0, const FloatRGBColor& color1)
{
	return FloatRGBColor(std::max(color0.r, color1.r),
		std::max(color0.g, color1.g),
		std::max(color0.b, color1.b));
}

inline FloatRGBColor min(const FloatRGBColor& color0, const FloatRGBColor& color1)
{
	return FloatRGBColor(std::min(color0.r, color1.r),
		std::min(color0.g, color1.g),
		std::min(color0.b, color1.b));
}

inline FloatRGBColor clamp(const FloatRGBColor& color, const FloatRGBColor& min, const FloatRGBColor& max)
{
	return ::min(::max(color, min), max);
}

inline FloatRGBColor lerp(const FloatRGBColor& color0, const FloatRGBColor& color1, float t)
{
	return (1.f - t) * color0 + t * color1;
}


#endif
