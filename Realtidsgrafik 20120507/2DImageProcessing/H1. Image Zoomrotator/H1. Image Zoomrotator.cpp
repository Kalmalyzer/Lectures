
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
	float scale = (float) sin(elapsedTime * 2.f) + 1.5f;

	float minX = 0.f;
	float minY = 0.f;
	float maxX = (float) ScreenWidth;
	float maxY = (float) ScreenHeight;

	float ca = (float) cos(angle);
	float sa = (float) sin(angle);

	float x0 = minX;
	float y0 = minY;
	float u0 = ((x0 - centerX) * ca - (y0 - centerY) * sa) * scale + centerX;
	float v0 = ((x0 - centerX) * sa + (y0 - centerY) * ca) * scale + centerY;

	float x1 = maxX;
	float y1 = minY;
	float u1 = ((x1 - centerX) * ca - (y1 - centerY) * sa) * scale + centerX;
	float v1 = ((x1 - centerX) * sa + (y1 - centerY) * ca) * scale + centerY;

	float x2 = maxX;
	float y2 = maxY;
	float u2 = ((x2 - centerX) * ca - (y2 - centerY) * sa) * scale + centerX;
	float v2 = ((x2 - centerX) * sa + (y2 - centerY) * ca) * scale + centerY;

	float x3 = minX;
	float y3 = maxY;
	float u3 = ((x3 - centerX) * ca - (y3 - centerY) * sa) * scale + centerX;
	float v3 = ((x3 - centerX) * sa + (y3 - centerY) * ca) * scale + centerY;

	TextureTriangleSpanTableRenderer triangleRenderer1(x0, y0, u0, v0, x1, y1, u1, v1, x3, y3, u3, v3, texture);
	triangleRenderer1.render(output);

	TextureTriangleSpanTableRenderer triangleRenderer2(x3, y3, u3, v3, x1, y1, u1, v1, x2, y2, u2, v2, texture);
	triangleRenderer2.render(output);
}
