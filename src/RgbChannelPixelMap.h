#ifndef _RGBCHANNELPIXELMAP_H_
#define _RGBCHANNELPIXELMAP_H_

#include "PixelMap.h"

class RgbChannelPixelMap : public PixelMap {
public:
	virtual QRgb map(int r, int g, int b);
protected:
	virtual int channelMap(int level) = 0;
};

#endif /* _RGBCHANNELPIXELMAP_H_ */
