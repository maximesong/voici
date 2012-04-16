#include "IteratorArea.h"

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
