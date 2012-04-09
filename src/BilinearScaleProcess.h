#ifndef _BILINEARSCALEPROCESS_H_
#define _BILINEARSCALEPROCESS_H_

#include "ScaleProcess.h"

class QImage;

class BilinearScaleProcess : public ScaleProcess {
public:
	BilinearScaleProcess(int width, int height);
	virtual QImage generateNewImage(const QImage &image);
};

#endif /* _BILINEARSCALEPROCESS_H_ */
