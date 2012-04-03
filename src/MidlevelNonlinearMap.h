#ifndef _MIDLEVELNONLINEARMAP_H_
#define _MIDLEVELNONLINEARMAP_H_

#include "RgbChannelPixelMap.h"

class MidlevelNonlinearMap : public RgbChannelPixelMap {
public:
	MidlevelNonlinearMap(double c, int max_level);
protected:
	virtual int channelMap(int level);
private:
	double m_c;
	int m_max;
};

#endif /* _MIDLEVELNONLINEARMAP_H_ */
