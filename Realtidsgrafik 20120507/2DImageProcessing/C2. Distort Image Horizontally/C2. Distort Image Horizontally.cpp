
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
	float distortStepTimeScale = 5.f;
	float distortStepY = 0.2f;

	float widthStepTimeScale = 0.2f;
	float widthStepY = 0.02f;

	float distortMaxWidth = 20.f;

	for (int y = 0; y < ScreenHeight; y++)
	{
		float maxWidth = (float) (sin(elapsedTime * widthStepTimeScale + y * widthStepY) * distortMaxWidth);

		int scrollPosition = (int) (sin(elapsedTime * distortStepTimeScale + y * distortStepY) * maxWidth);

		for (int x = 0; x < ScreenWidth; x++)
		{
			FloatRGBColor color = readPixel(originalImage, x + scrollPosition, y);
			drawPixel(output, x, y, color);
		}
	}
}
