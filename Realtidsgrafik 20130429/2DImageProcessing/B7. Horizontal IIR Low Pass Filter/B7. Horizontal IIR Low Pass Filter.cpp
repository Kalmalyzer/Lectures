
#include "../Main/Types.h"
#include "../Main/main.h"
#include "../Main/Image.h"
#include "../Main/FloatRGBColor.h"
#include "../Main/IIRFilter.h"
#include "../Main/RenderUtils.h"

Image* originalImage;
Image* tempImage;

void initEffect()
{
	originalImage = loadBmp("../images/OldSkool.bmp");
	tempImage = new Image(ScreenWidth, ScreenHeight);
}

void renderEffect(Image* output, double elapsedTime)
{
	float filterStrength = (float) (sin(elapsedTime * 2.0) * 0.5 + 0.5);

	applyIIRLowPassFilterRightward(originalImage, tempImage, filterStrength);
	applyIIRLowPassFilterLeftward(tempImage, output, filterStrength);
}
