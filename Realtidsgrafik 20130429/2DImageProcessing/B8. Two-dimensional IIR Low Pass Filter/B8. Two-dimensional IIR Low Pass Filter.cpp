
#include "../Main/Types.h"
#include "../Main/main.h"
#include "../Main/Image.h"
#include "../Main/FloatRGBColor.h"
#include "../Main/IIRFilter.h"
#include "../Main/RenderUtils.h"

Image* originalImage;
Image* tempImage0;
Image* tempImage1;

void initEffect()
{
	originalImage = loadBmp("../images/OldSkool.bmp");
	tempImage0 = new Image(ScreenWidth, ScreenHeight);
	tempImage1 = new Image(ScreenWidth, ScreenHeight);
}

void renderEffect(Image* output, double elapsedTime)
{
	float filterStrength = (float) (sin(elapsedTime * 2.0) * 0.5 + 0.5);

	applyIIRLowPassFilterRightward(originalImage, tempImage0, filterStrength);
	applyIIRLowPassFilterLeftward(tempImage0, tempImage1, filterStrength);
	applyIIRLowPassFilterDownward(tempImage1, tempImage0, filterStrength);
	applyIIRLowPassFilterUpward(tempImage0, output, filterStrength);
}
