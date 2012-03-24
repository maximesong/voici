#ifndef _PROCESSFACTORY_H_
#define _PROCESSFACTORY_H_

#include <QVector>

#include "VoiciGlobal.h"

class ImageProcess;
class PixelMap;

class ProcessFactory {
public:
	ProcessFactory();
	static ImageProcess *getStandardGrayProcess();
	static ImageProcess *getBinaryProcess(int low = 0, 
						 int high = MAX_PIXEL_VALUE);
	static ImageProcess *getConvolutionProcess(int rows, int columns, 
						   int centerRow, int centerColumn,
						   const QVector<double> &matrix);
private:
	static ImageProcess *buildFromPixelMap(PixelMap *map);
};

#endif /* _PROCESSFACTORY_H_ */
