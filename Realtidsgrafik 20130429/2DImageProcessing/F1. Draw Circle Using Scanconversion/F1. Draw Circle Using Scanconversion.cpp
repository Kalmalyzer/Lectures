
#include "../Main/Types.h"
#include "../Main/main.h"
#include "../Main/Image.h"
#include "../Main/FloatRGBColor.h"
#include "../Main/RenderUtils.h"
#include "../Main/ScanConversionRenderer.h"

void initEffect()
{
}

class CircleScanConversionRenderer : public ScanConversionRenderer
{
public:
	CircleScanConversionRenderer(int centerX, int centerY, float radius, FloatRGBColor insideColor)
		: m_centerX(centerX)
		, m_centerY(centerY)
		, m_radiusSquared(radius * radius)
		, m_insideColor(insideColor)
	{ }

	virtual bool computeSpanExtent(int y, int& start, int& end)
	{
		int dy = m_centerY - y;
		float dxSquared = m_radiusSquared - dy * dy;

		if (dxSquared > 0)
		{
			int dx = (int) sqrt(dxSquared);
			start = m_centerX - dx;
			end = m_centerX + dx;
			return true;
		}
		else
			return false;
	}

	virtual FloatRGBColor getInsideColor() { return m_insideColor; }

private:
	int m_centerX;
	int m_centerY;
	float m_radiusSquared;

	FloatRGBColor m_insideColor;
};

void renderEffect(Image* output, double elapsedTime)
{
	for (uint i = 0; i < ScreenWidth * ScreenHeight; i++)
		output->m_pixels[i] = FloatRGBColor(0.f, 0.f, 0.f);

	int centerX = ScreenWidth / 2;
	int centerY = ScreenHeight / 2;
	float radius = (float) (100.0 + 50.0 * sin(elapsedTime * 3.0));

	CircleScanConversionRenderer circleRenderer(centerX, centerY, radius, FloatRGBColor(255.f, 255.f, 255.f));

	circleRenderer.render(output);
}
