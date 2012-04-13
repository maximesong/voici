#include "PixelIterator.h"

#include <QImage>

#include "PixelMap.h"

PixelIterator::PixelIterator(int x, int y, int width, int height)
{
	setRange(x, y, width, height);
}

void PixelIterator::rawIterate(QImage *image, PixelMap *map)
{
	/* This may need to be fixed */
	QRgb *rgb = (QRgb *) image->bits();
	QRgb *y_rgb;
	QRgb *x_rgb;
	for (int j = 0; j != image->height(); ++j) {
		y_rgb = rgb + j * image->width();
		for (int i = 0; i != image->width(); ++i) {
			x_rgb = (y_rgb + i);
			QRgb map_value = map->map(*x_rgb);
			memcpy(x_rgb, &map_value, sizeof(QRgb));
		}
	}
}

void PixelIterator::iterate(QImage *image, PixelMap *map)
{
	if (m_x >= image->width() || m_y >= image->height())
		return;
	int x_end = image->width();
	if (m_width >= 0 && (m_x + m_width) < image->width())
		x_end = m_x + m_width;

	int y_end = image->height();
	if (m_height >= 0 && (m_x + m_height) < image->height())
		y_end = m_x + m_height;

	/* This may need to be fixed */
	QRgb *rgb = (QRgb *) image->bits();
	QRgb *y_rgb;
	QRgb *x_rgb;
	for (int j = m_y; j < y_end; ++j) {
		y_rgb = rgb + j * image->width();
		for (int i = m_x; i < x_end; ++i) {
			x_rgb = (y_rgb + i);
			QRgb map_value = map->map(*x_rgb);
			memcpy(x_rgb, &map_value, sizeof(QRgb));
		}
	}
}

void PixelIterator::iterate(QImage *image, PositionalPixelMap *map)
{
	if (m_x >= image->width() || m_y >= image->height())
		return;
	int x_end = image->width();
	if (m_width >= 0 && (m_x + m_width) < image->width())
		x_end = m_x + m_width;

	int y_end = image->height();
	if (m_height >= 0 && (m_x + m_height) < image->height())
		y_end = m_x + m_height;

	for (int i = m_x; i < x_end; ++i)
		for (int j = m_y; j < y_end; ++j)
			image->setPixel(i, j, map->map(i, j, *image));
}

void PixelIterator::setRange(int x, int y, int width, int height)
{
	m_x = x >= 0 ? x : 0;
	m_y = y >= 0 ? y : 0;
	m_width = width;
	m_height = height;
}

void PixelIterator::setWidthAndHeight(int width, int height)
{
	setRange(m_x, m_y, width, height);
}

void PixelIterator::setStartPoint(int x, int y)
{
	setRange(x, y, m_width, m_height);
}

