#ifndef _RATEPIXELMAP_H_
#define _RATEPIXELMAP_H_

#include "GrayPixelMap.h"

class RatePixelMap : public GrayPixelMap {
public:
	RatePixelMap(double rRate, double gRate, double bRate);
protected:
	virtual int grayDegree(int r, int g, int b);
private:
	double m_r_rate;
	double m_g_rate;
	double m_b_rate;
};

#endif /* _RATEPIXELMAP_H_ */
