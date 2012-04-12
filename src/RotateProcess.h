#ifndef _ROTATEPROCESS_H_
#define _ROTATEPROCESS_H_

#include "ImageProcess.h"

class QImage;

class RotateProcess : public ImageProcess {
public:
	RotateProcess(double rotateAngle, 
		      const QString &processName = "Rotate Process");
	virtual QImage generateNewImage(const QImage &image) = 0;

	virtual bool canApplyToRgb() { return 1; }

	virtual bool canApplyToGray() { return 1; }
protected:
	double counter_clock_rotate_angle;
};

#endif /* _ROTATEPROCESS_H_ */
