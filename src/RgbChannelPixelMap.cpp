#include "RgbChannelPixelMap.h"

QRgb RgbChannelPixelMap::map(int r, int g, int b)
{
	int r_new = channelMap(r);
	int g_new = channelMap(g);
	int b_new = channelMap(b);
	return qRgb(r_new, g_new, b_new);
}
