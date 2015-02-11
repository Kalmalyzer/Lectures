
#define _USE_MATH_DEFINES
#include <cmath>

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

void computeTextureCoordinates(float x, float y, float uOffset, float vOffset, float* u, float* v)
{
	float dx = x - (ScreenWidth / 2);
	float dy = y - (ScreenHeight / 2);

	float angle = atan2(dy, dx);

	float dist = (float) sqrt(dx * dx + dy * dy);

	*u = (float) fmod((angle / (2 * M_PI) + 1.f) * ScreenWidth + uOffset, ScreenWidth);
	*v = (float) fmod((20000.f / dist) + vOffset, ScreenHeight);
}

void renderEffect(Image* output, double elapsedTime)
{
	for (uint i = 0; i < ScreenWidth * ScreenHeight; i++)
		output->m_pixels[i] = FloatRGBColor(0.f, 0.f, 0.f);


	float uOffset = (float) (elapsedTime * 50.0);
	float vOffset = (float) (elapsedTime * 100.0);

	GridVertex grid[(GridResolutionX + 1) * (GridResolutionY + 1)];

	for (int gridY = 0; gridY < GridResolutionY + 1; gridY++)
		for (int gridX = 0; gridX < GridResolutionX + 1; gridX++)
		{
			GridVertex& vertex = grid[gridY * (GridResolutionX + 1) + gridX];
			vertex.x = (float) gridX * GridSquareSize;
			vertex.y = (float) gridY * GridSquareSize;

			computeTextureCoordinates(vertex.x, vertex.y, uOffset, vOffset, &vertex.u, &vertex.v);
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
