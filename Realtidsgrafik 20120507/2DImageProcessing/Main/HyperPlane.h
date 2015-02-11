
#ifndef HYPERPLANE_H
#define HYPERPLANE_H

/*
   HyperPlane describes a 2D hyperplane; that is, a 2d line in general form:
        Ax + By + C = 0
   Its intended use is to divide 2D space into two half-spaces, and to check
    which of the two half-spaces (the front or the back half-space) given points
    are located in.
 */

class HyperPlane
{
public:
	HyperPlane(float a, float b, float c)
		: m_a(a)
		, m_b(b)
		, m_c(c)
	{ }

	HyperPlane(float x0, float y0, float x1, float y1)
	{
		float dx = x1 - x0;
		float dy = y1 - y0;

		m_a = -dy;
		m_b = dx;
		m_c = -(x0 * m_a + y0 * m_b);
	}

	float distance(float x, float y)
	{
		return x * m_a + y * m_b + m_c;
	}

	bool isOnFrontSide(float x, float y)
	{
		return distance(x,y) >= 0;
	}

private:
	float m_a;
	float m_b;
	float m_c;
};

#endif
