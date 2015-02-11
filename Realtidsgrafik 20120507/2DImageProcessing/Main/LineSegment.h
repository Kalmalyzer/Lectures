
#ifndef LINESEGMENT_H
#define LINESEGMENT_H

/*
   LineSegment represents a 2D line, which you intend to intersect against
    horizontal lines (that is, you intend to compute "what is the X coordinate
	at which this line intersects row Y on-screen?").
 */

class LineSegment
{
public:
	LineSegment(float x0, float y0, float x1, float y1)
		: m_x0(x0)
		, m_y0(y0)
		, m_x1(x1)
		, m_y1(y1)
	{ }

	float intersectAgainstHorizontalLine(float y)
	{
		float t = (y - m_y0) / (m_y1 - m_y0);
		float x = t * (m_x1 - m_x0) + m_x0;
		return x;
	}

private:
	float m_x0;
	float m_y0;
	float m_x1;
	float m_y1;
};

#endif
