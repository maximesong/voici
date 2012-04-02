#include "MidlevelNonlinearMap.h"

MidlevelNonlinearMap::MidlevelNonlinearMap(int c, int max_level)
{
	m_c = c;
	m_max = max_level;
}

int MidlevelNonlinearMap::channelMap(int level)
{
	return safe_range(level + m_c * level * (m_max - level));
}
