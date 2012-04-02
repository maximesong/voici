#include "RatePixelMap.h"

RatePixelMap::RatePixelMap(double rRate, double gRate, double bRate)
{
	m_r_rate = rRate;
	m_g_rate = gRate;
	m_b_rate = bRate;
}

int RatePixelMap::mapToGray(int r, int g, int b) {
	return safe_range(r * m_r_rate + g * m_g_rate + b * m_b_rate);
}
