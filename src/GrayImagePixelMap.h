#ifndef _GRAYIMAGEPIXELMAP_H_
#define _GRAYIMAGEPIXELMAP_H_

#include "PixelMap.h"

class GrayImagePixelMap : public PixelMap {
public:
	virtual QRgb map(int r, int g = 0, int b = 0);
protected:
	virtual int channelMap(int level) = 0;
};

#endif /* _GRAYIMAGEPIXELMAP_H_ */
