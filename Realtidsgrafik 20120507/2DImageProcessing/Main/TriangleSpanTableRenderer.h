
#ifndef TRIANGLESPANTABLERENDERER_H
#define TRIANGLESPANTABLERENDERER_H

/*
   TriangleSpanTableRenderer generates spans for a triangle.

   Use it by subclassing TriangleSpanTableRenderer and implementing
    rasterizeSpans() to fill pixels with the per-pixel fill logic that
    you desire.
 */

#include "SpanTableRenderer.h"

class TriangleSpanTableRenderer : public SpanTableRenderer
{
public:
	TriangleSpanTableRenderer(float x0, float y0, float x1, float y1, float x2, float y2)
		: m_x0(x0)
		, m_y0(y0)
		, m_x1(x1)
		, m_y1(y1)
		, m_x2(x2)
		, m_y2(y2)
	{ }

protected:
	void generateEdge(int x0, int y0, int x1, int y1);

	virtual void generateSpans();

	float m_x0;
	float m_y0;
	float m_x1;
	float m_y1;
	float m_x2;
	float m_y2;
};

#endif
