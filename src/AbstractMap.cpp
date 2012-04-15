#include "AbstractMap.h"

uchar ByteMap::map(uchar src, int, int)
{
	return map(src);
}

QRgb RgbMap::map(uchar r, uchar g, uchar b, uchar a, int, int)
{
	return map(r, g, b, a);
}
