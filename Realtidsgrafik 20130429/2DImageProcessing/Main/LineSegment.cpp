
#include "Types.h"
#include "LineSegment.h"

LineSegment::LineSegment(float x0, float y0, float x1, float y1)
: m_x0(x0)
, m_y0(y0)
, m_x1(x1)
, m_y1(y1)
{
}

float LineSegment::intersectAgainstHorizontalLine(float y)
{
	float t = (y - m_y0) / (m_y1 - m_y0);
	float x = t * (m_x1 - m_x0) + m_x0;
	return x;
}
