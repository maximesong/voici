#ifndef _IMAGEBLENDMAP_H_
#define _IMAGEBLENDMAP_H_

#include "ImagePixelMap.h"

class ImageBlendMapPolicy;

class ImageBlendMap : public ImagePixelMap {
public:
	ImageBlendMap(const QImage &image, ImageBlendMapPolicy *policy);
	~ImageBlendMap();
	virtual QRgb map(int x, int y, int r, int g, int b);
	virtual QRgb map(int x, int y, const QImage &image);
	void setPolicy(ImageBlendMapPolicy *policy);
private:
	ImageBlendMapPolicy *m_policy;
};

#endif /* _IMAGEBLENDMAP_H_ */
