
#include "Types.h"
#include "TriangleGradient.h"

TriangleGradient::TriangleGradient(float x0, float y0, float c0,
	float x1, float y1, float c1,
	float x2, float y2, float c2)
{
	float dx01 = x1 - x0;
	float dx02 = x2 - x0;
	float dy01 = y1 - y0;
	float dy02 = y2 - y0;
	float dc01 = c1 - c0;
	float dc02 = c2 - c0;

	float denom = dx01 * dy02 - dx02 * dy01;
	float inverseDenom = 1.f / denom;

	m_dcdx = (dc01 * dy02 - dc02 * dy01) * inverseDenom;
	m_dcdy = (dc02 * dx01 - dc01 * dx02) * inverseDenom;
	m_c00 = c0 -(x0 * m_dcdx + y0 * m_dcdy);
}

float TriangleGradient::evaluate(float x, float y)
{
	return m_c00 + x * m_dcdx + y * m_dcdy;
}
