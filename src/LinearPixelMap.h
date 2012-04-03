#ifndef _LINEARPIXELMAP_H_
#define _LINEARPIXELMAP_H_

#include "RgbChannelPixelMap.h"

class LinearPixelMap : public RgbChannelPixelMap {
public:
	LinearPixelMap(double k, double b);
	virtual int channelMap(int level);
private:
	double m_k;
	double m_b;
};

#endif /* _LINEARPIXELMAP_H_ */
