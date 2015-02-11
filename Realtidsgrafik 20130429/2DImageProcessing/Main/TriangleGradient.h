
#ifndef TRIANGLEGRADIENT_H
#define TRIANGLEGRADIENT_H

/*
  TriangleGradient describes a parameter that varies linearly over a
   2D surface. If you specify the value of the parameter in three different
   locations (that must not be collinear) in 2D space, you can then evaluate
   the value of the parameter at any (x,y) location in 2D space after that.

  This is mainly used for interpolating texture coordinates and color values
   over the surface of a triangle.
 */

class TriangleGradient
{
public:
	TriangleGradient(float x0, float y0, float c0,
		float x1, float y1, float c1,
		float x2, float y2, float c2);

	float evaluate(float x, float y);

private:
	float m_dcdx;
	float m_dcdy;
	float m_c00;

};

#endif
