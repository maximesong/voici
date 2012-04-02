#ifndef _IMAGEBLENDMAP_H_
#define _IMAGEBLENDMAP_H_

#include "ImagePixelMap.h"

class ImageBlendMap : public ImagePixelMap {
public:
	ImageBlendMap(const QImage &image, double origin_rate, double new_rate);
	virtual QRgb map(int x, int y, int r, int g, int b);
	virtual QRgb map(int x, int y, const QImage &image);
	void setBlendRate(double origin_rate, double new_rate);
private:
	double m_origin_rate;
	double m_new_rate;
};

#endif /* _IMAGEBLENDMAP_H_ */
