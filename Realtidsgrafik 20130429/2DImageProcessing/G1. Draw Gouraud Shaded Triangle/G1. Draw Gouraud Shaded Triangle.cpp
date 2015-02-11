
#include "../Main/Types.h"
#include "../Main/main.h"
#include "../Main/Image.h"
#include "../Main/FloatRGBColor.h"
#include "../Main/LineSegment.h"
#include "../Main/RenderUtils.h"
#include "../Main/TriangleSpanTableRenderer.h"
#include "../Main/TriangleGradient.h"

void initEffect()
{
}

class GouraudTriangleSpanTableRenderer : public TriangleSpanTableRenderer
{
public:
	GouraudTriangleSpanTableRenderer(float x0, float y0, float c0, float x1, float y1, float c1, float x2, float y2, float c2, const FloatRGBColor& color)
		: TriangleSpanTableRenderer(x0, y0, x1, y1, x2, y2)
		, m_cGradient(x0, y0, c0, x1, y1, c1, x2, y2, c2)
		, m_color(color)
	{ }

	void rasterizeSpans(Image* output)
	{
		for (int y = 0; y < ScreenHeight; y++)
		{
			const Span& span = m_spans[y];

			for (int x = span.m_start; x < span.m_end; x++)
			{
				float c = m_cGradient.evaluate((float) x, (float) y);
				float intensity = c * (1.f / 255.f);

				drawPixel(output, x, y, intensity * m_color);
			}
		}
	}

private:
	TriangleGradient m_cGradient;
	FloatRGBColor m_color;
};

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
	float c0 = 0.f;
	float x1 = (float) (centerX + cos(angle + 0.f) * radius);
	float y1 = (float) (centerY - sin(angle + 0.f) * radius);
	float c1 = 255.f;
	float x2 = (float) (centerX + cos(angle + 4.5f) * radius);
	float y2 = (float) (centerY - sin(angle + 4.5f) * radius);
	float c2 = 130.f;

	GouraudTriangleSpanTableRenderer triangleRenderer(x0, y0, c0, x1, y1, c1, x2, y2, c2, FloatRGBColor(255.f, 255.f, 255.f));

	triangleRenderer.render(output);
}
