
#include "FloatRGBColor.h"
#include "Image.h"
#include "main.h"
#include "ScanConversionRenderer.h"
#include "RenderUtils.h"

void ScanConversionRenderer::render(Image* output, const FloatRGBColor& color)
{
	for (int y = 0; y < ScreenHeight; y++)
	{
		int start, end;
		if (computeSpanExtent(y, start, end))
		{
			for (int x = start; x < end; x++)
				drawPixel(output, x, y, color);
		}
	}
}
