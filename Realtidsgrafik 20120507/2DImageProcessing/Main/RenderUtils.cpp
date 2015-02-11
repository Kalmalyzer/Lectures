
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

void applyFIRFilterHorizontal(Image* input, Image* output, int numTaps, float* tapStrengths)
{
	ASSERT(input->m_width == output->m_width && input->m_height == output->m_height);
	ASSERT((numTaps % 2) == 1);

	int startXOffset = -(numTaps - 1) / 2;

	for (int y = 0; y < output->m_height; y++)
		for (int x = 0; x < output->m_width; x++)
		{
			FloatRGBColor accumulatedColor(0.f, 0.f, 0.f);
			for (int tap = 0; tap < numTaps; tap++)
				accumulatedColor += readPixel(input, x + startXOffset + tap, y) * tapStrengths[tap];

			drawPixel(output, x, y, accumulatedColor);
		}
}

void applyFIRFilter(Image* input, Image* output, int numTapsX, int numTapsY, float* tapStrengths)
{
	ASSERT(input->m_width == output->m_width && input->m_height == output->m_height);
	ASSERT((numTapsX % 2) == 1);
	ASSERT((numTapsY % 2) == 1);

	int startXOffset = -(numTapsX - 1) / 2;
	int startYOffset = -(numTapsY - 1) / 2;

	for (int y = 0; y < output->m_height; y++)
		for (int x = 0; x < output->m_width; x++)
		{
			FloatRGBColor accumulatedColor(0.f, 0.f, 0.f);
			for (int tapY = 0; tapY < numTapsY; tapY++)
				for (int tapX = 0; tapX < numTapsX; tapX++)
				{
					int inputTapX = x + startXOffset + tapX;
					int inputTapY = y + startYOffset + tapY;
					int tapIndex = tapY * numTapsX + tapX;
					accumulatedColor += readPixel(input, inputTapX, inputTapY) * tapStrengths[tapIndex];
				}

			drawPixel(output, x, y, accumulatedColor);
		}
}

void applyIIRLowPassFilterRightward(Image* input, Image* output, float strength)
{
	ASSERT(input->m_width == output->m_width && input->m_height == output->m_height);

	for (int y = 0; y < output->m_height; y++)
		for (int x = 0; x < output->m_width; x++)
		{
			FloatRGBColor previousColor = readPixel(output, x - 1, y);
			FloatRGBColor desiredColor = readPixel(input, x, y);
			FloatRGBColor finalColor = lerp(previousColor, desiredColor, 1.f - strength);
			drawPixel(output, x, y, finalColor);
		}
}

void applyIIRLowPassFilterLeftward(Image* input, Image* output, float strength)
{
	ASSERT(input->m_width == output->m_width && input->m_height == output->m_height);

	for (int y = 0; y < output->m_height; y++)
		for (int x = output->m_width - 1; x >= 0; x--)
		{
			FloatRGBColor previousColor = readPixel(output, x + 1, y);
			FloatRGBColor desiredColor = readPixel(input, x, y);
			FloatRGBColor finalColor = lerp(previousColor, desiredColor, 1.f - strength);
			drawPixel(output, x, y, finalColor);
		}
}

void applyIIRLowPassFilterDownward(Image* input, Image* output, float strength)
{
	ASSERT(input->m_width == output->m_width && input->m_height == output->m_height);

	for (int x = 0; x < output->m_width; x++)
		for (int y = 0; y < output->m_height; y++)
		{
			FloatRGBColor previousColor = readPixel(output, x, y - 1);
			FloatRGBColor desiredColor = readPixel(input, x, y);
			FloatRGBColor finalColor = lerp(previousColor, desiredColor, 1.f - strength);
			drawPixel(output, x, y, finalColor);
		}
}

void applyIIRLowPassFilterUpward(Image* input, Image* output, float strength)
{
	ASSERT(input->m_width == output->m_width && input->m_height == output->m_height);

	for (int x = 0; x < output->m_width; x++)
		for (int y = output->m_height - 1; y >= 0; y--)
		{
			FloatRGBColor previousColor = readPixel(output, x, y + 1);
			FloatRGBColor desiredColor = readPixel(input, x, y);
			FloatRGBColor finalColor = lerp(previousColor, desiredColor, 1.f - strength);
			drawPixel(output, x, y, finalColor);
		}
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
