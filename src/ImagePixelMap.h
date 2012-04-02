#ifndef _IMAGEPIXELMAP_H_
#define _IMAGEPIXELMAP_H_

#include <QImage>

#include "PositionalPixelMap.h"

class ImagePixelMap : public PositionalPixelMap {
public:
	virtual QRgb map(int x, int y, const QImage &image) = 0;
	void setImage(const QImage &image);
	int getWidth();
	int getHeight();
protected:
	QImage m_image;
};

#endif /* _IMAGEPIXELMAP_H_ */
