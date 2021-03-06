
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
	float fadeStrength = (float) (sin(elapsedTime * 2.0) * 0.5 + 0.5);

	for (uint i = 0; i < ScreenWidth * ScreenHeight; i++)
		output->m_pixels[i] = originalImage->m_pixels[i] * fadeStrength;
}
