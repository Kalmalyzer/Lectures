
#include "../Main/Types.h"
#include "../Main/main.h"
#include "../Main/Image.h"
#include "../Main/FloatRGBColor.h"
#include "../Main/RenderUtils.h"

void initEffect()
{
}

void renderEffect(Image* output, double elapsedTime)
{
	for (uint i = 0; i < ScreenWidth * ScreenHeight; i++)
		output->m_pixels[i] = FloatRGBColor(0.f, 0.f, 0.f);

	int x0 = 10;
	int y0 = 10;
	int x1 = 630;
	int y1 = 470;

	float slope = ((float) (y1 - y0)) / (x1 - x0);

	float y = (float) y0;
	for (int x = x0; x <= x1; x++)
	{
		drawPixel(output, x, (int) y, FloatRGBColor(255.f, 255.f, 255.f));
		y += slope;
	}
}
