#ifndef _LINEARPIXELMAP_H_
#define _LINEARPIXELMAP_H_

#include "RgbChannelPixelMap.h"

class LinearPixelMap : public RgbChannelPixelMap {
public:
	LinearPixelMap(int k, int b);
	virtual int channelMap(int level);
private:
	int m_k;
	int m_b;
};

#endif /* _LINEARPIXELMAP_H_ */
