
#include "../Main/Types.h"
#include "../Main/main.h"
#include "../Main/Image.h"
#include "../Main/FloatRGBColor.h"
#include "../Main/LineSegment.h"
#include "../Main/RenderUtils.h"
#include "../Main/TextureTriangleSpanTableRenderer.h"

Image* texture;

void initEffect()
{
	texture = loadBmp("../images/OldSkool.bmp");
}

void renderEffect(Image* output, double elapsedTime)
{
	for (uint i = 0; i < ScreenWidth * ScreenHeight; i++)
		output->m_pixels[i] = FloatRGBColor(0.f, 0.f, 0.f);

	float centerX = ScreenWidth * 0.5f;
	float centerY = ScreenHeight * 0.5f;
	float radius = 200.f;
	float angle = (float) elapsedTime * 1.f;

	float x0 = (float) (centerX + cos(angle + 2.f) * radius);
	float y0 = (float) (centerY - sin(angle + 2.f) * radius);
	float u0 = 300.f;
	float v0 = 0.f;
	float x1 = (float) (centerX + cos(angle + 0.f) * radius);
	float y1 = (float) (centerY - sin(angle + 0.f) * radius);
	float u1 = 500.f;
	float v1 = 200.f;
	float x2 = (float) (centerX + cos(angle + 4.5f) * radius);
	float y2 = (float) (centerY - sin(angle + 4.5f) * radius);
	float u2 = 300.f;
	float v2 = 350.f;

	TextureTriangleSpanTableRenderer triangleRenderer(x0, y0, u0, v0, x1, y1, u1, v1, x2, y2, u2, v2, texture);

	triangleRenderer.render(output);
}
