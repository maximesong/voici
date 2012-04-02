#include "PixelMap.h"
#include "VoiciGlobal.h"

QRgb PixelMap::map(QRgb pixel)
{
	int r = qRed(pixel);
	int g = qGreen(pixel);
	int b = qBlue(pixel);
	return map(r, g, b);
}

int PixelMap::safe_range(int level)
{
	if (level > MAX_PIXEL_VALUE)
		return MAX_PIXEL_VALUE;
	if (level < 0)
		return 0;
	return level;
}
