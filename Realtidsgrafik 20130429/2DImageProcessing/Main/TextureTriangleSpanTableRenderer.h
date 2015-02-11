
#ifndef TEXTURETRIANGLESPANTABLERENDERER_H
#define TEXTURETRIANGLESPANTABLERENDERER_H

/*
  TextureTriangleSpanTableRenderer draws a triangle which has a
   2D texture mapped linearly onto itself.

   This is accomplished by specifying UV coordinates (coordinates in
   texture space) at each vertex of the triangle, then interpolating
   these UV coordinates independently over the triangle,
   and finally performing a texture lookup for each pixel to be drawn.
 */

#include "TriangleSpanTableRenderer.h"
#include "TriangleGradient.h"

class TextureTriangleSpanTableRenderer : public TriangleSpanTableRenderer
{
public:
	TextureTriangleSpanTableRenderer(float x0, float y0, float u0, float v0,
		float x1, float y1, float u1, float v1,
		float x2, float y2, float u2, float v2,
		Image* texture)
		: TriangleSpanTableRenderer(x0, y0, x1, y1, x2, y2)
		, m_uGradient(x0, y0, u0, x1, y1, u1, x2, y2, u2)
		, m_vGradient(x0, y0, v0, x1, y1, v1, x2, y2, v2)
		, m_texture(texture)
	{ }

	void rasterizeSpans(Image* output);

private:

	TriangleGradient m_uGradient;
	TriangleGradient m_vGradient;

	Image* m_texture;
};

#endif
