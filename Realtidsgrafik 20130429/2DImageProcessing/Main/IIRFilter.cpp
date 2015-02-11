
#include "Types.h"
#include "IIRFilter.h"
#include "Assert.h"
#include "FloatRGBColor.h"
#include "Image.h"
#include "RenderUtils.h"

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

