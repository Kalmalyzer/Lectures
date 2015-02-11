
#include "../Main/Types.h"
#include "../Main/main.h"
#include "../Main/Image.h"
#include "../Main/FloatRGBColor.h"
#include "../Main/RenderUtils.h"

void initEffect()
{
}

void renderEffect(Image* output, double elapsedTime)
{
	for (uint i = 0; i < ScreenWidth * ScreenHeight; i++)
		output->m_pixels[i] = FloatRGBColor(0.f, 0.f, 0.f);

	drawRectangle(output,  10,  10,  90,  90, FloatRGBColor(255.f,   0.f,   0.f));
	drawRectangle(output, 110,  10, 190,  90, FloatRGBColor(  0.f, 255.f,   0.f));
	drawRectangle(output, 210,  10, 290,  90, FloatRGBColor(  0.f,   0.f, 255.f));

	drawRectangle(output,  10, 110,  90, 190, FloatRGBColor(  0.f,   0.f,   0.f));
	drawRectangle(output, 110, 110, 190, 190, FloatRGBColor(128.f, 128.f, 128.f));
	drawRectangle(output, 210, 110, 290, 190, FloatRGBColor(255.f, 255.f, 255.f));

	drawRectangle(output,  10, 210,  90, 290, FloatRGBColor(255.f, 255.f,   0.f));
	drawRectangle(output, 110, 210, 190, 290, FloatRGBColor(255.f,   0.f, 255.f));
	drawRectangle(output, 210, 210, 290, 290, FloatRGBColor(  0.f, 255.f, 255.f));
}
