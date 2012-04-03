#include "LinearBlendPolicy.h"

#include "VoiciGlobal.h"

LinearBlendPolicy::LinearBlendPolicy(double firstRate, double secondRate)
{
	setRate(firstRate, secondRate);
}

int LinearBlendPolicy::channelBlend(int firstLevel, int secondLevel)
{
	return legalized_level(m_first_rate * firstLevel + 
			       m_second_rate * secondLevel);
}

void LinearBlendPolicy::setFirstRate(double rate)
{
	m_first_rate = rate;
}

void LinearBlendPolicy::setSecondRate(double rate)
{
	m_second_rate = rate;
}

void LinearBlendPolicy::setRate(double firstRate, double secondRate)
{
	setFirstRate(firstRate);
	setSecondRate(secondRate);
}
