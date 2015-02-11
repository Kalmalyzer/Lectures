
#include "TriangleSpanTableRenderer.h"

void TriangleSpanTableRenderer::generateEdge(int x0, int y0, int x1, int y1)
{
	if (y1 > y0)
	{
		// Right edge, downward
		float slope = (float) (x1 - x0) / (y1 - y0);

		float x = (float) x0;
		for (int y = y0; y < y1; y++)
		{
			if (y >= 0 && y < ScreenHeight)
			{
				m_spans[y].m_end = (int) x;
				x += slope;
			}
		}
	}
	else
	{
		// Left edge, upward
		float slope = (float) (x1 - x0) / (y1 - y0);

		float x = (float) x1;
		for (int y = y1; y < y0; y++)
		{
			if (y >= 0 && y < ScreenHeight)
			{
				m_spans[y].m_start = (int) x;
				x += slope;
			}
		}
	}
}

void TriangleSpanTableRenderer::generateSpans()
{
	generateEdge((int) m_x0, (int) m_y0, (int) m_x1, (int) m_y1);
	generateEdge((int) m_x1, (int) m_y1, (int) m_x2, (int) m_y2);
	generateEdge((int) m_x2, (int) m_y2, (int) m_x0, (int) m_y0);
}
