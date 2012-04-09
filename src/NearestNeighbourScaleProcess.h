#ifndef _NEARESTNEIGHBOURSCALEPROCESS_H_
#define _NEARESTNEIGHBOURSCALEPROCESS_H_

#include "ScaleProcess.h"

class QImage;

class NearestNeighbourScaleProcess : public ScaleProcess {
public:
	NearestNeighbourScaleProcess(int width, int height);
	virtual QImage generateNewImage(const QImage &image);
};

#endif /* _NEARESTNEIGHBOURSCALEPROCESS_H_ */
