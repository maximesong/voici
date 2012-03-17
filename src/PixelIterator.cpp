#include "PixelIterator.h"

#include <QImage>

#include "PixelMap.h"

void PixelIterator::iterate(QImage *image, PixelMap *map)
{
	for (int i = 0; i != image->width(); ++i)
		for (int j = 0; j != image->height(); ++j) {
			QRgb rgb = image->pixel(i, j);
			image->setPixel(i, j, map->map(rgb));
		}
}
