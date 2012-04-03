#ifndef _QUOTIENTBLENDPOLICY_H_
#define _QUOTIENTBLENDPOLICY_H_

#include "ImageBlendMapPolicy.h"

class QuotientBlendPolicy : public ImageBlendMapPolicy {
public:
	QuotientBlendPolicy(double coefficient);
	virtual int channelBlend(int firstLevel, int secondLevel);
private:
	double m_c;
};

#endif /* _QUOTIENTBLENDPOLICY_H_ */
