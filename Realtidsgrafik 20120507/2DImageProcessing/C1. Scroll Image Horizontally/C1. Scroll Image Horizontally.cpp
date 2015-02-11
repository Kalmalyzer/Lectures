
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
	float pixelsPerSecond = 200.f;

	int scrollPosition = (int) fmod(elapsedTime * pixelsPerSecond, (double) (2 * ScreenWidth)) - ScreenWidth;

	for (int y = 0; y < ScreenHeight; y++)
		for (int x = 0; x < ScreenWidth; x++)
		{
			FloatRGBColor color = readPixel(originalImage, x + scrollPosition, y);
			drawPixel(output, x, y, color);
		}
}
