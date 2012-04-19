#include "IteratorArea.h"

#include <iostream>
using namespace std;

RectangleIteratorArea::RectangleIteratorArea(int x, int y, int width, int height)
{
	m_start_x = x;
	m_start_y = y;
	m_end_x = x + width;
	m_end_y = y + height;
}

int RectangleIteratorArea::startX()
{
	return m_start_x;
}

int RectangleIteratorArea::startY()
{
	return m_start_y;
}

int RectangleIteratorArea::endX()
{
	return m_end_x;
}

int RectangleIteratorArea::endY()
{
	return m_end_y;
}

bool RectangleIteratorArea::contains(int x, int y)
{
	return x >= m_start_x && x < m_end_x && y >= m_start_y && y < m_end_y;
}

bool RectangleIteratorArea::inside_contains(int, int)
{
	return true;
}

EllipseIteratorArea::EllipseIteratorArea(int cx, int cy, int rx, int ry)
{
	m_cx = cx;
	m_cy = cy;
	m_rx = rx;
	m_ry = ry;
	m_start_x = cx - rx;
	m_start_y = cy - ry;
	m_end_x = cx + rx;
	m_end_y = cy + ry;
}

int EllipseIteratorArea::startX()
{
	return m_start_x;
}

int EllipseIteratorArea::startY()
{
	return m_start_y;
}

int EllipseIteratorArea::endX()
{
	return m_end_x;
}

int EllipseIteratorArea::endY()
{
	return m_end_y;
}

bool EllipseIteratorArea::contains(int x, int y)
{
	return x >= m_start_x && x < m_end_x && y >= m_start_y && y < m_end_y
		&& inside_contains(x, y);
}

bool EllipseIteratorArea::inside_contains(int x, int y)
{
	return ((m_cx - x) * (m_cx - x) /  double(m_rx * m_rx) +
		(m_cy - y) * (m_cy - y) /  double(m_ry * m_ry)) < 1;
}
