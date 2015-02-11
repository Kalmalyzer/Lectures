
#include "../Main/Types.h"
#include "../Main/main.h"
#include "../Main/Image.h"
#include "../Main/FloatRGBColor.h"
#include "../Main/RenderUtils.h"

Image* originalImage;
Image* filteredImage;

void initEffect()
{
	originalImage = loadBmp("../images/OldSkool.bmp");
	filteredImage = new Image(ScreenWidth, ScreenHeight);
}

void renderEffect(Image* output, double elapsedTime)
{
	float blendPosition = (float) (sin(elapsedTime * 2.0) * 0.5 + 0.5);

	enum { NumTapsX = 31 };
	enum { NumTapsY = 31 };

	float tapStrengths[NumTapsX * NumTapsY];

	for (uint i = 0; i < NumTapsX * NumTapsY; i++)
		tapStrengths[i] = 1.f / (NumTapsX * NumTapsY);

	applyFIRFilter(originalImage, filteredImage, NumTapsX, NumTapsY, tapStrengths);

	for (uint i = 0; i < ScreenWidth * ScreenHeight; i++)
	{
		output->m_pixels[i] = lerp(originalImage->m_pixels[i], filteredImage->m_pixels[i], blendPosition);
	}
}
