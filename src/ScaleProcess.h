#ifndef _SCALEPROCESS_H_
#define _SCALEPROCESS_H_

#include "ImageProcess.h"

class QImage;

class ScaleProcess : public ImageProcess {
public:
	ScaleProcess(int width, int height);
	void setHeight(int height);
	void setWidth(int width);
	void setScale(int width, int height);
	virtual QImage generateNewImage(const QImage &image) = 0;
protected:
	int m_width;
	int m_height;
};

#endif /* _SCALEPROCESS_H_ */
