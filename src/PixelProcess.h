#ifndef _PIXELPROCESS_H_
#define _PIXELPROCESS_H_

class PixelMap;
class QImage;

#include "ImageProcess.h"

class PixelProcess : public ImageProcess {
public:
	PixelProcess(PixelMap *map);
	~PixelProcess();
protected:
	virtual QImage generateNewImage(const QImage &image);
private:
	PixelMap *m_map;
};

#endif /* _PIXELPROCESS_H_ */
