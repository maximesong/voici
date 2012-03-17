#ifndef _GRAYPIXELMAP_H_
#define _GRAYPIXELMAP_H_

#include <QColor>

#include "PixelMap.h"

class GrayPixelMap : public PixelMap {
public:
	virtual QRgb map(int r, int g, int b);
protected:
	virtual int grayDegree(int r, int g, int b) = 0;
};


#endif /* _GRAYPIXELMAP_H_ */
