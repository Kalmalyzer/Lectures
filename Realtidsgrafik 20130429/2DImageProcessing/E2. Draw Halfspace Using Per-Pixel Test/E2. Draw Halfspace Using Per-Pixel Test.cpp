
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

class HalfSpacePerPixelTestRenderer : public PerPixelTestRenderer
{
public:
	HalfSpacePerPixelTestRenderer(HyperPlane hyperPlane, FloatRGBColor insideColor)
		: m_hyperPlane(hyperPlane)
		, m_insideColor(insideColor)
	{ }

	virtual bool isInside(int x, int y)
	{
		bool isOnFrontSide = m_hyperPlane.isOnFrontSide((float) x, (float) y);

		return isOnFrontSide;
	}

	virtual FloatRGBColor getInsideColor() { return m_insideColor; }

private:
	HyperPlane m_hyperPlane;
	FloatRGBColor m_insideColor;
};

void renderEffect(Image* output, double elapsedTime)
{
	for (uint i = 0; i < ScreenWidth * ScreenHeight; i++)
		output->m_pixels[i] = FloatRGBColor(0.f, 0.f, 0.f);

	float x0 = 10;
	float y0 = 200;
	float x1 = 630;
	float y1 = 300;
	HyperPlane hyperPlane(x0, y0, x1, y1);

	HalfSpacePerPixelTestRenderer halfSpaceRenderer(hyperPlane, FloatRGBColor(255.f, 255.f, 255.f));

	halfSpaceRenderer.render(output);
}
