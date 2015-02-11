
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
	HyperPlane(float a, float b, float c);

	HyperPlane(float x0, float y0, float x1, float y1);

	float distance(float x, float y) const;

	bool isOnFrontSide(float x, float y) const;

private:
	float m_a;
	float m_b;
	float m_c;
};

#endif
