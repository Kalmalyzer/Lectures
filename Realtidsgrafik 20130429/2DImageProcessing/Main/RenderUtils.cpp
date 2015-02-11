
#include "Types.h"
#include "Assert.h"
#include "FloatRGBColor.h"
#include "Image.h"
#include "RenderUtils.h"

FloatRGBColor readPixel(Image* output, int x, int y)
{
	if (x >= 0 && x < output->m_width && y >= 0 && y < output->m_height)
	{
		int offset = y * output->m_width + x;
		return output->m_pixels[offset];
	}
	else
		return FloatRGBColor(0.f, 0.f, 0.f);
}

void drawPixel(Image* output, int x, int y, const FloatRGBColor& color)
{
	if (x >= 0 && x < output->m_width && y >= 0 && y < output->m_height)
	{
		int offset = y * output->m_width + x;
		output->m_pixels[offset] = color;
	}
}

void drawRectangle(Image* output, int x0, int y0, int x1, int y1, const FloatRGBColor& color)
{
	for (int y = y0; y < y1; y++)
		for (int x = x0; x < x1; x++)
			drawPixel(output, x, y, color);
}

void magnify2X(Image* input, Image* output, int centerX, int centerY)
{
	ASSERT((output->m_width % 2) == 0);
	ASSERT((output->m_height % 2) == 0);

	int sourceWidth = output->m_width / 2;
	int sourceHeight = output->m_height / 2;
	int sourceStartX = centerX - (sourceWidth / 2);
	int sourceStartY = centerY - (sourceHeight / 2);
	int sourceEndX = sourceStartX + sourceWidth;
	int sourceEndY = sourceStartY + sourceHeight;

	for (int sourceY = sourceStartY, destY = 0; sourceY < sourceEndY; sourceY++, destY += 2)
	{
		for (int sourceX = sourceStartX, destX = 0; sourceX < sourceEndX; sourceX++, destX += 2)
		{
			FloatRGBColor color = readPixel(input, sourceX, sourceY);
			drawPixel(output, destX,     destY    , color);
			drawPixel(output, destX + 1, destY    , color);
			drawPixel(output, destX,     destY + 1, color);
			drawPixel(output, destX + 1, destY + 1, color);
		}
	}
}
