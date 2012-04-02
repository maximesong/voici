#include "LinearPixelMap.h"

LinearPixelMap::LinearPixelMap(int k, int b)
{
	m_k = k;
	m_b = b;
}

int LinearPixelMap::channelMap(int level)
{
	return safe_range(m_k * level + m_b);
}
