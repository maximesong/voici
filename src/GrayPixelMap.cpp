#include "GrayPixelMap.h"

QRgb GrayPixelMap::map(int r, int g, int b)
{
	int gray = mapToGray(r, g, b);
	return qRgb(gray, gray, gray);
}



