
#include "../Main/Types.h"
#include "../Main/main.h"
#include "../Main/Image.h"
#include "../Main/FloatRGBColor.h"
#include "../Main/RenderUtils.h"

Image* originalImage;

void initEffect()
{
	originalImage = loadBmp("../images/OldSkool.bmp");
}

void renderEffect(Image* output, double elapsedTime)
{
	for (uint i = 0; i < ScreenWidth * ScreenHeight; i++)
		output->m_pixels[i] = FloatRGBColor(0.f, 0.f, 0.f);

	float zoomFactor = 1.f / (float) (sin(elapsedTime * 2.0) * 4.0 + 4.25);

	for (int y = 0; y < ScreenHeight; y++)
		for (int x = 0; x < ScreenWidth; x++)
		{
			int sourceX = (int) (x * zoomFactor);
			int sourceY = (int) (y * zoomFactor);
			int destX = x;
			int destY = y;
			FloatRGBColor color = readPixel(originalImage, sourceX, sourceY);
			drawPixel(output, destX, destY, color);
		}
}
