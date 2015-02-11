
#include "../Main/Types.h"
#include "../Main/main.h"
#include "../Main/Image.h"
#include "../Main/FloatRGBColor.h"
#include "../Main/HyperPlane.h"
#include "../Main/RenderUtils.h"
#include "../Main/PerPixelTestRenderer.h"

void initEffect()
{
}

class TrianglePerPixelTestRenderer : public PerPixelTestRenderer
{
public:
	TrianglePerPixelTestRenderer(float x0, float y0, float x1, float y1, float x2, float y2)
		: m_edge0(x0, y0, x1, y1)
		, m_edge1(x1, y1, x2, y2)
		, m_edge2(x2, y2, x0, y0)
	{ }

	virtual bool isInside(int x, int y)
	{
		bool isOnFrontSide0 = m_edge0.isOnFrontSide((float) x, (float) y);
		bool isOnFrontSide1 = m_edge1.isOnFrontSide((float) x, (float) y);
		bool isOnFrontSide2 = m_edge2.isOnFrontSide((float) x, (float) y);

		return isOnFrontSide0 && isOnFrontSide1 && isOnFrontSide2;
	}

private:
	HyperPlane m_edge0;
	HyperPlane m_edge1;
	HyperPlane m_edge2;
};

void renderEffect(Image* output, double elapsedTime)
{
	for (uint i = 0; i < ScreenWidth * ScreenHeight; i++)
		output->m_pixels[i] = FloatRGBColor(0.f, 0.f, 0.f);

	float x0 = 10;
	float y0 = 200;
	float x1 = 630;
	float y1 = 300;
	float x2 = 300;
	float y2 = 400;

	TrianglePerPixelTestRenderer triangleRenderer(x0, y0, x1, y1, x2, y2);

	triangleRenderer.render(output, FloatRGBColor(255.f, 255.f, 255.f));
}
