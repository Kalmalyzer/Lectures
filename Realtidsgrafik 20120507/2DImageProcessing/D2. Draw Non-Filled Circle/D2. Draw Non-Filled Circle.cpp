#define _USE_MATH_DEFINES
#include <cmath>

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

	int centerX = ScreenWidth / 2;
	int centerY = ScreenHeight / 2;
	float radius = (float) (100.0 + 50.0 * sin(elapsedTime * 3.0));
	int numPixels = 200;

	float angle = 0.f;
	float angleStep = (float) ((2 * M_PI) / numPixels);

	for (int i = 0; i < numPixels; i++)
	{
		int x = (int) (centerX + cos(angle) * radius);
		int y = (int) (centerY + sin(angle) * radius);
		drawPixel(output, x, y, FloatRGBColor(255.f, 255.f, 255.f));
		angle += angleStep;
	}
}
