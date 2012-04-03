#include "QuotientBlendPolicy.h"

#include "VoiciGlobal.h"

QuotientBlendPolicy::QuotientBlendPolicy(double coefficient)
{
	m_c = coefficient;
}

int QuotientBlendPolicy::channelBlend(int firstLevel, int secondLevel)
{
	if (secondLevel == 0)
		secondLevel = 1;
	return legalized_level(m_c * (firstLevel / secondLevel));
}
