#include "GrayPixelMap.h"


QRgb GrayPixelMap::map(int r, int g, int b)
{
	int grey = grayDegree(r, g, b);
	return qRgb(grey, grey, grey);
}



