#ifndef _RANGETHRESHOLDMAP_H_
#define _RANGETHRESHOLDMAP_H_

#include "GrayPixelMap.h"
#include "VoiciGlobal.h"

class RangeThresholdMap : public GrayPixelMap {
public:
	RangeThresholdMap(int low = 0, int high = MAX_PIXEL_VALUE);
	void setLow(int low) { m_low = low; }
	void setHigh(int high) { m_high = high; }
	int getLow() { return m_low; }
	int getHigh() { return m_high; }

	virtual int grayDegree(int r, int g, int b);
private:
	int m_low;
	int m_high;
};

#endif /* _RANGETHRESHOLDMAP_H_ */
