#include "ProcessFactory.h"

#include "PixelMap.h"
#include "PixelProcess.h"
#include "ImageProcess.h"
#include "RatePixelMap.h"
#include "LinearPixelMap.h"
#include "RangeThresholdMap.h"
#include "MatrixBlockMap.h"
#include "BlockIterator.h"
#include "BlockProcess.h"
#include "MidlevelNonlinearMap.h"
#include "ImageBlendMap.h"
#include "AlgebraicProcess.h"
#include "ImageBlendMapPolicy.h"
#include "ProductBlendPolicy.h"
#include "QuotientBlendPolicy.h"
#include "LinearBlendPolicy.h"
#include "QuickGaussBlurProcess.h"
#include "NearestNeighbourScaleProcess.h"
#include "BilinearScaleProcess.h"
#include "NearestNeighbourRotateProcess.h"
#include "MedianBlockMap.h"
#include "MeanBlockMap.h"

ImageProcess *ProcessFactory::getStandardGrayProcess()
{
	PixelMap *map = new RatePixelMap(0.299, 0.587, 0.114);
	return buildFromPixelMap(map);
}


ImageProcess *ProcessFactory::getBinaryProcess(int low, int high)
{
	PixelMap *map = new RangeThresholdMap(low, high);
	return buildFromPixelMap(map);
}

ImageProcess *ProcessFactory::buildFromPixelMap(PixelMap *map)
{
	return new PixelProcess(map);
}

ImageProcess *ProcessFactory::getConvolutionProcess(int rows, int columns,
						    int centerRow, int centerColumn,
						    const QVector<double> &matrix)
{
	BlockIterator *iter = new BlockIterator(rows, columns, centerRow, centerColumn);
	BlockMap *map = new MatrixBlockMap(rows, columns, matrix);
	BlockProcess *process = new BlockProcess(iter, map, "Convolution");
	return process;
}

ImageProcess *ProcessFactory::getLinearProcess(double k, double b)
{
	PixelMap *map = new LinearPixelMap(k, b);
	return buildFromPixelMap(map);
}

ImageProcess *ProcessFactory::getMidlevelNonlinearMap(double c, int max_level)
{
	PixelMap *map = new MidlevelNonlinearMap(c, max_level);
	return buildFromPixelMap(map);
}

ImageProcess *ProcessFactory::getImageLinearBlendProcess(const QImage &image,
							 double rate1, 
							 double rate2)
{
	ImageBlendMapPolicy *policy = new LinearBlendPolicy(rate1, rate2);
	return buildAlgebraicProcess(image, policy);
}

ImageProcess *ProcessFactory::getImageProductProcess(const QImage &image,
					    double coefficient)
{
	ImageBlendMapPolicy *policy = new ProductBlendPolicy(coefficient);
	return buildAlgebraicProcess(image, policy);
}

ImageProcess *ProcessFactory::getImageQuotientProcess(const QImage &image,
					     double coefficient)
{
	ImageBlendMapPolicy *policy = new QuotientBlendPolicy(coefficient);
	return buildAlgebraicProcess(image, policy);
}


ImageProcess *ProcessFactory::buildAlgebraicProcess(const QImage &image, 
						    ImageBlendMapPolicy *policy)
{
	ImagePixelMap *map  = new ImageBlendMap(image, policy);
	AlgebraicProcess *process = new AlgebraicProcess(map);
	return process;
}

ImageProcess *ProcessFactory::getQuickGaussBlurProcess(double horz, double vert)
{
	return new QuickGaussBlurProcess(horz, vert);
}

ImageProcess *ProcessFactory::getBilinearScaleProcess(int width, int height)
{
	return new BilinearScaleProcess(width, height);
}

ImageProcess *ProcessFactory::getNearestNeighbourScaleProcess(int width, 
							      int height)
{
	return new NearestNeighbourScaleProcess(width, height);
}

ImageProcess *ProcessFactory::getNearestNeighbourRotateProcess(double rotateAngle)
{
	return new NearestNeighbourRotateProcess(rotateAngle);
}

ImageProcess *ProcessFactory::getMedianFilterProcess(int m, int n)
{
	BlockIterator *iter = new BlockIterator(m, n, (m + 1) / 2, (n + 1) / 2);
	BlockMap *map = new MedianBlockMap(m, n);
	BlockProcess *process = new BlockProcess(iter, map, "Median Filter");
	return process;
}

ImageProcess *ProcessFactory::getMeanFilterProcess(int m, int n)
{
	BlockIterator *iter = new BlockIterator(m, n, (m + 1) / 2, (n + 1) / 2);
	BlockMap *map = new MeanBlockMap(m, n);
	BlockProcess *process = new BlockProcess(iter, map, "Median Filter");
	return process;
}
