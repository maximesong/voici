#include "BlockIterator.h"

#include <QImage>

#include "BlockMap.h"

BlockIterator::BlockIterator(int m, int n, int x, int y)
{
	m_m = m;
	m_n = n;
	m_x = x;
	m_y = y;
	rx_offset = x - m_m;
	ry_offset = y - m_n;
}

void BlockIterator::iterate(QImage *image, BlockMap *map)
{
	for (int i = m_m - 1; i != image->width(); ++i)
		for (int j = m_n - 1; j != image->height(); ++j) {
			QRgb rgb = map->map(i - m_m + 1, j- m_n + 1, image);
			image->setPixel(i + rx_offset, j + ry_offset, rgb);
		}
}
