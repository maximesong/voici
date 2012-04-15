#ifndef _PROCESSFACTORY_H_
#define _PROCESSFACTORY_H_

#include <QVector>
#include <QImage>

#include "VoiciGlobal.h"
#include "ImageProcesser.h"

class ProcessFactory {
public:
	ProcessFactory();
	static SharedImageProcesser getStandardGrayProcess();
	static SharedImageProcesser getBinaryProcess(int low = 0, 
						 int high = MAX_PIXEL_VALUE);
	static SharedImageProcesser getConvolutionProcess(int rows, int columns, 
						   int centerRow, int centerColumn,
						   const QVector<double> &matrix);
	static SharedImageProcesser getLinearProcess(double k, double b);
	static SharedImageProcesser getMidlevelNonlinearMap(double c, int max_level);
	
	static SharedImageProcesser getImageLinearBlendProcess(const QImage &image,
							double rate1, 
							double rate2);

	static SharedImageProcesser getImageProductProcess(const QImage &image,
						    double coefficient = 1.0);
	static SharedImageProcesser getImageQuotientProcess(const QImage &image,
						     double coefficient = 1.0);
	
	static SharedImageProcesser getQuickGaussBlurProcess(double vert, double horz);

	static SharedImageProcesser getBilinearScaleProcess(int width, int height);

	static SharedImageProcesser getNearestNeighbourScaleProcess(int width, 
							     int height);

	static SharedImageProcesser getNearestNeighbourRotateProcess(double rotateAngle);

	static SharedImageProcesser getMedianFilterProcess(int m, int n);
	static SharedImageProcesser getMeanFilterProcess(int m, int n);
private:
	static SharedImageProcesser buildDynamicProcess(SharedImageProcesser processer);
	static SharedImageProcesser buildPreProcess(SharedImageProcesser processer);
	static SharedImageProcesser buildPostProcess(SharedImageProcesser processer);

	static SharedImageProcesser buildFromPixelMap(PixelMap *map);
	static SharedImageProcesser buildAlgebraicProcess(const QImage &image, 
						   ImageBlendMapPolicy *policy);
};

#endif /* _PROCESSFACTORY_H_ */
