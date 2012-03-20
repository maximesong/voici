#ifndef _PIXELPROCESS_H_
#define _PIXELPROCESS_H_

#include "ImageProcess.h"

class PixelMap;
class QImage;

class PixelProcess : public ImageProcess {
public:
	PixelProcess(PixelMap *map, const QString &processName = "Pixel Process");
	~PixelProcess();
	void setPixelMap(PixelMap *map);
protected:
	virtual QImage generateNewImage(const QImage &image);
private:
	PixelMap *m_map;
};

#endif /* _PIXELPROCESS_H_ */
