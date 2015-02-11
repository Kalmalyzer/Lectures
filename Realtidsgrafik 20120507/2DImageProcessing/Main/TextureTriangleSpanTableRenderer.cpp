
#include "FloatRGBColor.h"
#include "RenderUtils.h"
#include "TextureTriangleSpanTableRenderer.h"

void TextureTriangleSpanTableRenderer::rasterizeSpans(Image* output)
{
	for (int y = 0; y < ScreenHeight; y++)
	{
		const Span& span = m_spans[y];

		for (int x = span.m_start; x < span.m_end; x++)
		{
			float u = m_uGradient.evaluate((float) x, (float) y);
			float v = m_vGradient.evaluate((float) x, (float) y);

			FloatRGBColor color = readPixel(m_texture, (int) u, (int) v);
			drawPixel(output, x, y, color);
		}
	}
}
