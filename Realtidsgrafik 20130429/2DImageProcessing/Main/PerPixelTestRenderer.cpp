
#include "FloatRGBColor.h"
#include "Image.h"
#include "PerPixelTestRenderer.h"
#include "RenderUtils.h"

void PerPixelTestRenderer::render(Image* output)
{
	FloatRGBColor insideColor = getInsideColor();

	for (int y = 0; y < output->m_height; y++)
		for (int x = 0; x < output->m_width; x++)
		{
			if (isInside(x, y))
				drawPixel(output, x, y, insideColor);
		}
}