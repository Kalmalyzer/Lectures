
#include "../Main/Types.h"
#include "../Main/main.h"
#include "../Main/Image.h"
#include "../Main/FloatRGBColor.h"
#include "../Main/LineSegment.h"
#include "../Main/RenderUtils.h"
#include "../Main/TextureTriangleSpanTableRenderer.h"

Image* texture;

enum { GridSquareSize = 8 };

enum { GridResolutionX = (ScreenWidth / GridSquareSize) };
enum { GridResolutionY = (ScreenHeight / GridSquareSize) };

struct GridVertex
{
	float x;
	float y;
	float u;
	float v;
};

void initEffect()
{
	texture = loadBmp("../images/OldSkool.bmp");
}

void applyDeformation(float centerX, float centerY, float maxStrength, float radius, float* x, float* y)
{
	float dx = *x - centerX;
	float dy = *y - centerY;

	float dist = (float) sqrt(dx * dx + dy * dy);

	float invDist = 0.f;
	if (dist > 0.01f)
		invDist = 1.f / dist;
	else
		invDist = 100.f;

	float strength = std::max((radius - dist) / radius, 0.f);

	float displacementDistance = maxStrength * strength;

	*x += dx * invDist * displacementDistance;
	*y += dy * invDist * displacementDistance;
}

void renderEffect(Image* output, double elapsedTime)
{
	for (uint i = 0; i < ScreenWidth * ScreenHeight; i++)
		output->m_pixels[i] = FloatRGBColor(0.f, 0.f, 0.f);

	float movementRadius = 200.f;
	float angle = (float) elapsedTime * 1.f;
	float centerX = ScreenWidth * 0.5f + (float) cos(angle) * movementRadius;
	float centerY = ScreenHeight * 0.5f - (float) sin(angle) * movementRadius;

	float maxStrength = 50.f;
	float radius = 100.f;

	GridVertex grid[(GridResolutionX + 1) * (GridResolutionY + 1)];

	for (int gridY = 0; gridY < GridResolutionY + 1; gridY++)
		for (int gridX = 0; gridX < GridResolutionX + 1; gridX++)
		{
			GridVertex& vertex = grid[gridY * (GridResolutionX + 1) + gridX];
			float x = (float) gridX * GridSquareSize;
			float y = (float) gridY * GridSquareSize;
			float u = x;
			float v = y;

			applyDeformation(centerX, centerY, maxStrength, radius, &x, &y);

			vertex.x = x;
			vertex.y = y;
			vertex.u = u;
			vertex.v = v;
		}

	for (int gridY = 0; gridY < GridResolutionY; gridY++)
		for (int gridX = 0; gridX < GridResolutionX; gridX++)
		{
			GridVertex& vertex0 = grid[(gridY + 0) * (GridResolutionX + 1) + (gridX + 0)];
			GridVertex& vertex1 = grid[(gridY + 0) * (GridResolutionX + 1) + (gridX + 1)];
			GridVertex& vertex2 = grid[(gridY + 1) * (GridResolutionX + 1) + (gridX + 1)];
			GridVertex& vertex3 = grid[(gridY + 1) * (GridResolutionX + 1) + (gridX + 0)];

			TextureTriangleSpanTableRenderer triangleRenderer1(vertex0.x, vertex0.y, vertex0.u, vertex0.v,
				vertex1.x, vertex1.y, vertex1.u, vertex1.v,
				vertex3.x, vertex3.y, vertex3.u, vertex3.v,
				texture);
			triangleRenderer1.render(output);

			TextureTriangleSpanTableRenderer triangleRenderer2(vertex3.x, vertex3.y, vertex3.u, vertex3.v,
				vertex1.x, vertex1.y, vertex1.u, vertex1.v,
				vertex2.x, vertex2.y, vertex2.u, vertex2.v,
				texture);
			triangleRenderer2.render(output);
		}

}
