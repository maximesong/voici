#include "PixelMap.h"

QRgb PixelMap::map(int x, int y, const QImage &image)
{
	return map(image.pixel(x, y));
}

QRgb PixelMap::map(QRgb pixel)
{
	int r = qRed(pixel);
	int g = qGreen(pixel);
	int b = qBlue(pixel);
	return map(r, g, b);
}

