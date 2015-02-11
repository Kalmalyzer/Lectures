
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

	float zoomFactor = (float) (sin(elapsedTime * 2.0) + 1.5);

	for (int y = 0; y < ScreenHeight; y++)
		for (int x = 0; x < ScreenWidth; x++)
		{
			int sourceX = x;
			int sourceY = y;
			int destX = (int) (x * zoomFactor);
			int destY = (int) (y * zoomFactor);
			FloatRGBColor color = readPixel(originalImage, sourceX, sourceY);
			drawPixel(output, destX, destY, color);
		}
}
