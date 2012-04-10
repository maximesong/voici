#ifndef _NEARESTNEIGHBOURROTATEPROCESS_H_
#define _NEARESTNEIGHBOURROTATEPROCESS_H_

#include "RotateProcess.h"

class QImage;

class NearestNeighbourRotateProcess : public RotateProcess {
public:
	NearestNeighbourRotateProcess(double rotateAngle);
	virtual QImage generateNewImage(const QImage &image);
};

#endif /* _NEARESTNEIGHBOURROTATEPROCESS_H_ */

