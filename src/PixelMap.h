#ifndef _PIXELMAP_H_
#define _PIXELMAP_H_

#include <QColor>
#include "PositionalPixelMap.h"

class PixelMap : public PositionalPixelMap {
public:
	virtual QRgb map(int x, int y, const QImage &image);
	virtual QRgb map(QRgb pixel);
	virtual QRgb map(int r, int g, int b) = 0;
};


#endif /* _PIXELMAP_H_ */
