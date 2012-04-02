#include "GrayImagePixelMap.h"

QRgb GrayImagePixelMap::map(int r, int, int)
{
	int gray = channelMap(r);
	return qRgb(gray, gray, gray);
}
