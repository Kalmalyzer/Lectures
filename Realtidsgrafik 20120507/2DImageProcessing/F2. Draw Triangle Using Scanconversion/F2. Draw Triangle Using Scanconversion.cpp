
#include "../Main/Types.h"
#include "../Main/main.h"
#include "../Main/Image.h"
#include "../Main/FloatRGBColor.h"
#include "../Main/LineSegment.h"
#include "../Main/RenderUtils.h"
#include "../Main/ScanConversionRenderer.h"

void initEffect()
{
}

class TriangleScanConversionRenderer : public ScanConversionRenderer
{
public:
	TriangleScanConversionRenderer(float x0, float y0, float x1, float y1, float x2, float y2)
		: m_line0(x0, y0, x1, y1)
		, m_line1(x1, y1, x2, y2)
		, m_line2(x2, y2, x0, y0)
		, m_isRight0(y1 > y0)
		, m_isRight1(y2 > y1)
		, m_isRight2(y0 > y2)
	{ }

	virtual bool computeSpanExtent(int y, int& start, int& end)
	{
		int x0 = (int) m_line0.intersectAgainstHorizontalLine((float) y);
		int x1 = (int) m_line1.intersectAgainstHorizontalLine((float) y);
		int x2 = (int) m_line2.intersectAgainstHorizontalLine((float) y);

		start = 0;
		end = ScreenWidth;

		if (m_isRight0)
			end = std::min(end, x0);
		else
			start = std::max(start, x0);

		if (m_isRight1)
			end = std::min(end, x1);
		else
			start = std::max(start, x1);

		if (m_isRight2)
			end = std::min(end, x2);
		else
			start = std::max(start, x2);

		if (start < end)
			return true;
		else
			return false;
	}

private:
	LineSegment m_line0;
	LineSegment m_line1;
	LineSegment m_line2;

	bool m_isRight0;
	bool m_isRight1;
	bool m_isRight2;
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

	TriangleScanConversionRenderer triangleRenderer(x0, y0, x1, y1, x2, y2);

	triangleRenderer.render(output, FloatRGBColor(255.f, 255.f, 255.f));
}
