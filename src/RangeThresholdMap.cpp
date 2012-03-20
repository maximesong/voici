#include "RangeThresholdMap.h"

RangeThresholdMap::RangeThresholdMap(int low, int high)
{
	m_low = low;
	m_high = high;
}


int RangeThresholdMap::grayDegree(int r, int, int)
{
	/* Assume that r == g && g == b */
	if (r >= m_low && r <= m_high)
		return 1;
	else
		return 0;
}
