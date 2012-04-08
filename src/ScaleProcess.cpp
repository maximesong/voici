#include "ScaleProcess.h"

#include <QImage>

ScaleProcess::ScaleProcess(int width, int height)
{
	setWidth(width);
	setHeight(height);
}

void ScaleProcess::setHeight(int height)
{
	if (height < 0)
		height = -height;
	m_height = height;
}

void ScaleProcess::setWidth(int width)
{
	if (width < 0)
		width = -width;
	m_width = width;
}

void ScaleProcess::setScale(int width, int height)
{
	setWidth(width);
	setHeight(height);
}
