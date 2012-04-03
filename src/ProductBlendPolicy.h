#ifndef _PRODUCTBLENDPOLICY_H_
#define _PRODUCTBLENDPOLICY_H_

#include "ImageBlendMapPolicy.h"

class ProductBlendPolicy : public ImageBlendMapPolicy {
public:
	ProductBlendPolicy(double coefficient);
	virtual int channelBlend(int firstLevel, int secondLevel);
private:
	double m_c;
};

#endif /* _PRODUCTBLENDPOLICY_H_ */
