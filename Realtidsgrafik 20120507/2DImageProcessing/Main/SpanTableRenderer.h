
#ifndef SPANTABLERENDERER_H
#define SPANTABLERENDERER_H

/*
   SpanTableRenderer implements the logic for rendering a
    shape through a 2-stage process; first the shape is
	converted into a set of spans, as described by the span table;
	then all spans wider than 0 pixels in the span table are rendered.

   Use it by subclassing SpanTableRenderer and implementing
    generateSpans() for turning your shape into a set of entries
	in the span table, and implementing rasterizeSpans()
	for drawing the actual spans.
 */

#include "main.h"

class FloatRGBColor;
class Image;

class SpanTableRenderer
{
public:
	void render(Image* output);

protected:
	class Span
	{
	public:
		Span()
		: m_start(ScreenWidth)
		, m_end(0)
		{ }

		int m_start;
		int m_end;
	};

	virtual void generateSpans() = 0;

	virtual void rasterizeSpans(Image* output) = 0;

	Span m_spans[ScreenHeight];
};

#endif
