
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
	float fadePosition = (float) (sin(elapsedTime * 2.0) * 0.5 + 0.5);

	for (uint i = 0; i < ScreenWidth * ScreenHeight; i++)
	{
		FloatRGBColor originalColor = originalImage->m_pixels[i];

		float greyScaleIntensity = (originalColor.r * 0.58f) + (originalColor.g * 0.30f) + (originalColor.b * 0.12f);
		FloatRGBColor greyScaleColor(greyScaleIntensity, greyScaleIntensity, greyScaleIntensity);
		FloatRGBColor color = lerp(originalColor, greyScaleColor, fadePosition);

		output->m_pixels[i] = color;
	}
}
