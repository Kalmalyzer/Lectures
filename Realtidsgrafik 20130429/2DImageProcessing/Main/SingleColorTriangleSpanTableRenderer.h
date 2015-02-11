
#ifndef SINGLECOLORTRIANGLESPANTABLERENDERER_H
#define SINGLECOLORTRIANGLESPANTABLERENDERER_H

/*
  SingleColorTriangleSpanTableRenderer draws a triangle
   that is filled with a single, constant color.
 */

#include "TriangleSpanTableRenderer.h"
#include "FloatRGBColor.h"

class SingleColorTriangleSpanTableRenderer : public TriangleSpanTableRenderer
{
public:
	SingleColorTriangleSpanTableRenderer(float x0, float y0, float x1, float y1, float x2, float y2, const FloatRGBColor& color)
		: TriangleSpanTableRenderer(x0, y0, x1, y1, x2, y2)
		, m_color(color)
	{ }
protected:

	virtual void rasterizeSpans(Image* output);

	FloatRGBColor m_color;
};

#endif
