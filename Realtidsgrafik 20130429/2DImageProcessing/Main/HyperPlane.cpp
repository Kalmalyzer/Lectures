
#include "Types.h"
#include "HyperPlane.h"

HyperPlane::HyperPlane(float a, float b, float c)
: m_a(a)
, m_b(b)
, m_c(c)
{
}

HyperPlane::HyperPlane(float x0, float y0, float x1, float y1)
{
	float dx = x1 - x0;
	float dy = y1 - y0;

	m_a = -dy;
	m_b = dx;
	m_c = -(x0 * m_a + y0 * m_b);
}

float HyperPlane::distance(float x, float y) const
{
	return x * m_a + y * m_b + m_c;
}

bool HyperPlane::isOnFrontSide(float x, float y) const
{
	return distance(x,y) >= 0;
}
