#include "ProductBlendPolicy.h"

#include "VoiciGlobal.h"

ProductBlendPolicy::ProductBlendPolicy(double coefficient)
{
	m_c = coefficient;
}

int ProductBlendPolicy::channelBlend(int firstLevel, int secondLevel)
{
	return legalized_level(m_c * (firstLevel * secondLevel));
}
