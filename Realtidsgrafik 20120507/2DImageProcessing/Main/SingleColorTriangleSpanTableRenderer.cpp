
#include "SingleColorTriangleSpanTableRenderer.h"
#include "RenderUtils.h"

void SingleColorTriangleSpanTableRenderer::rasterizeSpans(Image* output)
{
	for (int y = 0; y < ScreenHeight; y++)
	{
		const Span& span = m_spans[y];

		for (int x = span.m_start; x < span.m_end; x++)
			drawPixel(output, x, y, m_color);
	}
}
