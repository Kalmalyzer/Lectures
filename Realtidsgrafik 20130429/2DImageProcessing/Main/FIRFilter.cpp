
#include "Types.h"
#include "FIRFilter.h"
#include "Assert.h"
#include "FloatRGBColor.h"
#include "Image.h"
#include "RenderUtils.h"

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
