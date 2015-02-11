
#include "../Main/Types.h"
#include "../Main/main.h"
#include "../Main/Image.h"
#include "../Main/FloatRGBColor.h"
#include "../Main/RenderUtils.h"
#include "../Main/PerPixelTestRenderer.h"

void initEffect()
{
}

class CirclePerPixelTestRenderer : public PerPixelTestRenderer
{
public:
	CirclePerPixelTestRenderer(int centerX, int centerY, float radius)
		: m_centerX(centerX)
		, m_centerY(centerY)
		, m_radiusSquared(radius * radius)
	{ }

	virtual bool isInside(int x, int y)
	{
		int dx = x - m_centerX;
		int dy = y - m_centerY;
		int dx2_dy2 = dx * dx + dy * dy;

		return dx2_dy2 < m_radiusSquared;
	}

private:
	int m_centerX;
	int m_centerY;
	float m_radiusSquared;
};

void renderEffect(Image* output, double elapsedTime)
{
	for (uint i = 0; i < ScreenWidth * ScreenHeight; i++)
		output->m_pixels[i] = FloatRGBColor(0.f, 0.f, 0.f);

	int centerX = ScreenWidth / 2;
	int centerY = ScreenHeight / 2;
	float radius = (float) (100.0 + 50.0 * sin(elapsedTime * 3.0));

	CirclePerPixelTestRenderer circleRenderer(centerX, centerY, radius);

	circleRenderer.render(output, FloatRGBColor(255.f, 255.f, 255.f));
}
