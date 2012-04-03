#ifndef _LINEARBLENDPOLICY_H_
#define _LINEARBLENDPOLICY_H_

#include "ImageBlendMapPolicy.h"

class LinearBlendPolicy : public ImageBlendMapPolicy {
public:
	LinearBlendPolicy(double firstRate, double secondRate);
	virtual int channelBlend(int firstLevel, int secondLevel);
	void setFirstRate(double rate);
	void setSecondRate(double rate);
	void setRate(double firstRate, double secondRate);
private:
	double m_first_rate;
	double m_second_rate;
};

#endif /* _LINEARBLENDPOLICY_H_ */
