#ifndef _POSITIONALPIXELMAP_H_
#define _POSITIONALPIXELMAP_H_

#include <QImage>

class PositionalPixelMap {
public:
	virtual QRgb map(int x, int y, const QImage &image) = 0;
protected:
	virtual int safe_range(int level);
};

#endif /* _POSITIONALPIXELMAP_H_ */
