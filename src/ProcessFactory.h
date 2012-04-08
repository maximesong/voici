#ifndef _PROCESSFACTORY_H_
#define _PROCESSFACTORY_H_

#include <QVector>
#include <QImage>

#include "VoiciGlobal.h"

class ImageProcess;
class PixelMap;
class ImageBlendMapPolicy;

class ProcessFactory {
public:
	ProcessFactory();
	static ImageProcess *getStandardGrayProcess();
	static ImageProcess *getBinaryProcess(int low = 0, 
						 int high = MAX_PIXEL_VALUE);
	static ImageProcess *getConvolutionProcess(int rows, int columns, 
						   int centerRow, int centerColumn,
						   const QVector<double> &matrix);
	static ImageProcess *getLinearProcess(double k, double b);
	static ImageProcess *getMidlevelNonlinearMap(double c, int max_level);
	
	static ImageProcess *getImageLinearBlendProcess(const QImage &image,
							double rate1, 
							double rate2);

	static ImageProcess *getImageProductProcess(const QImage &image,
						    double coefficient = 1.0);
	static ImageProcess *getImageQuotientProcess(const QImage &image,
						     double coefficient = 1.0);
	
	static ImageProcess *getQuickGaussBlurProcess(double vert, double horz);
private:
	static ImageProcess *buildFromPixelMap(PixelMap *map);
	static ImageProcess *buildAlgebraicProcess(const QImage &image, 
						   ImageBlendMapPolicy *policy);
};

#endif /* _PROCESSFACTORY_H_ */
