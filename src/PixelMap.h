#ifndef _PIXELMAP_H_
#define _PIXELMAP_H_

#include <QColor>

class PixelMap {
public:
	virtual QRgb map(QRgb pixel);
	virtual QRgb map(int r, int g, int b) = 0;
protected:
	virtual int safe_range(int level);
};


#endif /* _PIXELMAP_H_ */
