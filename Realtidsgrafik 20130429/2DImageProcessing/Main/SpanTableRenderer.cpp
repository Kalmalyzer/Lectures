
#include "FloatRGBColor.h"
#include "Image.h"
#include "SpanTableRenderer.h"
#include "RenderUtils.h"

void SpanTableRenderer::render(Image* output)
{
	generateSpans();
	rasterizeSpans(output);
}
