#include "RangeThresholdMap.h"

#include <iostream>
using namespace std;

RangeThresholdMap::RangeThresholdMap(int low, int high)
{
	m_low = low;
	m_high = high;
}


int RangeThresholdMap::channelMap(int level)
{
	/* Assume that r == g && g == b */
	if (level >= m_low && level <= m_high)
		return 255;
	else
		return 0;
}
