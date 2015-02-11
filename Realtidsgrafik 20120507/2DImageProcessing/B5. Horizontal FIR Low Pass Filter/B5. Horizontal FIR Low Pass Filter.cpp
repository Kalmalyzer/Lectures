
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

	enum { NumTaps = 31 };

	float tapStrengths[NumTaps];

	for (uint i = 0; i < NumTaps; i++)
		tapStrengths[i] = 1.f / NumTaps;

	applyFIRFilterHorizontal(originalImage, filteredImage, NumTaps, tapStrengths);

	for (uint i = 0; i < ScreenWidth * ScreenHeight; i++)
	{
		output->m_pixels[i] = lerp(originalImage->m_pixels[i], filteredImage->m_pixels[i], blendPosition);
	}
}
