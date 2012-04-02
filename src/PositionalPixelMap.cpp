#include "PositionalPixelMap.h"

#include "VoiciGlobal.h"

int PositionalPixelMap::safe_range(int level)
{
	if (level > MAX_PIXEL_VALUE)
		return MAX_PIXEL_VALUE;
	if (level < 0)
		return 0;
	return level;
}
