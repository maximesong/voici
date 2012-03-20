#include "BlockIterator.h"

#include <QImage>

#include "BlockMap.h"

BlockIterator::BlockIterator(int m, int n, int x, int y)
{
	m_m = m;
	m_n = n;
	m_x = x;
	m_y = y;
	rx_offset = m_m - x;
	ry_offset = m_m - y;
}

void BlockIterator::iterate(QImage *image, BlockMap *map)
{
	for (int i = m_m - 1; i != image->width(); ++i)
		for (int j = m_n; j != image->height(); ++j) {
			QRgb rgb = map->map(i, j, image);
			image->setPixel(i + rx_offset, j + ry_offset, rgb);
		}
}
