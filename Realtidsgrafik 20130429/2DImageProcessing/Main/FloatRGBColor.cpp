
#include "Types.h"
#include "FloatRGBColor.h"

#include <cmath>
#include <algorithm>

FloatRGBColor::FloatRGBColor()
{
}

FloatRGBColor::FloatRGBColor(float r0, float g0, float b0)
: r(r0), g(g0), b(b0)
{
}

FloatRGBColor FloatRGBColor::operator +(const FloatRGBColor& color) const
{
	return FloatRGBColor(r + color.r, g + color.g, b + color.b);
}
	
FloatRGBColor FloatRGBColor::operator -(const FloatRGBColor& color) const
{
	return *this + (-color);
}

FloatRGBColor FloatRGBColor::operator *(float f) const
{
	return FloatRGBColor(r * f, g * f, b * f);
}

FloatRGBColor FloatRGBColor::operator +=(const FloatRGBColor& color)
{
	return *this = *this + color;
}

FloatRGBColor FloatRGBColor::operator -=(const FloatRGBColor& color)
{
	return *this = *this - color;
}

FloatRGBColor FloatRGBColor::operator *=(float f)
{
	return *this = *this * f;
}

FloatRGBColor operator -(const FloatRGBColor& color)
{
	return FloatRGBColor(-color.r, -color.g, -color.b);
}

FloatRGBColor operator *(float f, const FloatRGBColor& color)
{
	return color * f;
}

float dot(const FloatRGBColor& color0, const FloatRGBColor& color1)
{
	return color0.r * color1.r + color0.g * color1.g + color0.b * color1.b;
}

float length(const FloatRGBColor& color)
{
	return sqrt(dot(color, color));
}

FloatRGBColor normalize(const FloatRGBColor& color)
{
	return (1.f / length(color)) * color;
}

FloatRGBColor cross(const FloatRGBColor& color0, const FloatRGBColor& color1)
{
	return FloatRGBColor(color0.g * color1.b - color0.b * color1.g,
				color0.b * color1.r - color0.r * color1.b,
				color0.r * color1.g - color0.g * color1.r);
}

FloatRGBColor min(const FloatRGBColor& color0, const FloatRGBColor& color1)
{
	return FloatRGBColor(std::min(color0.r, color1.r),
		std::min(color0.g, color1.g),
		std::min(color0.b, color1.b));
}

FloatRGBColor max(const FloatRGBColor& color0, const FloatRGBColor& color1)
{
	return FloatRGBColor(std::max(color0.r, color1.r),
		std::max(color0.g, color1.g),
		std::max(color0.b, color1.b));
}

FloatRGBColor clamp(const FloatRGBColor& color, const FloatRGBColor& min, const FloatRGBColor& max)
{
	return ::min(::max(color, min), max);
}

FloatRGBColor lerp(const FloatRGBColor& color0, const FloatRGBColor& color1, float t)
{
	return (1.f - t) * color0 + t * color1;
}
