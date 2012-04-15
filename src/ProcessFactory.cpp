#include "ProcessFactory.h"

#include "Map.h"
#include "Iterator.h"

SharedImageProcesser ProcessFactory::getStandardGrayProcess(Iterator *iter)
{
	RgbMap *map = GrayRgbMap(0.299, 0.587, 0.114, 1);
	return buildFromPixelMap(map);
}


SharedImageProcesser ProcessFactory::getBinaryProcess(int low, int high)
{
	PixelMap *map = new RangeThresholdMap(low, high);
	return buildFromPixelMap(map);
}



SharedImageProcesser ProcessFactory::getConvolutionProcess(int rows, int columns,
						    int centerRow, int centerColumn,
						    const QVector<double> &matrix)
{
	BlockIterator *iter = new BlockIterator(rows, columns, centerRow, centerColumn);
	BlockMap *map = new MatrixBlockMap(rows, columns, matrix);
	BlockProcess *process = new BlockProcess(iter, map, "Convolution");
	return process;
}

SharedImageProcesser ProcessFactory::getLinearProcess(double k, double b)
{
	PixelMap *map = new LinearPixelMap(k, b);
	return buildFromPixelMap(map);
}

SharedImageProcesser ProcessFactory::getMidlevelNonlinearMap(double c, int max_level)
{
	PixelMap *map = new MidlevelNonlinearMap(c, max_level);
	return buildFromPixelMap(map);
}

SharedImageProcesser ProcessFactory::getImageLinearBlendProcess(const QImage &image,
							 double rate1, 
							 double rate2)
{
	ImageBlendMapPolicy *policy = new LinearBlendPolicy(rate1, rate2);
	return buildAlgebraicProcess(image, policy);
}

SharedImageProcesser ProcessFactory::getImageProductProcess(const QImage &image,
					    double coefficient)
{
	ImageBlendMapPolicy *policy = new ProductBlendPolicy(coefficient);
	return buildAlgebraicProcess(image, policy);
}

SharedImageProcesser ProcessFactory::getImageQuotientProcess(const QImage &image,
					     double coefficient)
{
	ImageBlendMapPolicy *policy = new QuotientBlendPolicy(coefficient);
	return buildAlgebraicProcess(image, policy);
}


SharedImageProcesser ProcessFactory::buildAlgebraicProcess(const QImage &image, 
						    ImageBlendMapPolicy *policy)
{
	ImagePixelMap *map  = new ImageBlendMap(image, policy);
	AlgebraicProcess *process = new AlgebraicProcess(map);
	return process;
}

SharedImageProcesser ProcessFactory::getQuickGaussBlurProcess(double horz, double vert)
{
	return new QuickGaussBlurProcess(horz, vert);
}

SharedImageProcesser ProcessFactory::getBilinearScaleProcess(int width, int height)
{
	return new BilinearScaleProcess(width, height);
}

SharedImageProcesser ProcessFactory::getNearestNeighbourScaleProcess(int width, 
							      int height)
{
	return new NearestNeighbourScaleProcess(width, height);
}

SharedImageProcesser ProcessFactory::getNearestNeighbourRotateProcess(double rotateAngle)
{
	return new NearestNeighbourRotateProcess(rotateAngle);
}

SharedImageProcesser ProcessFactory::getMedianFilterProcess(int m, int n)
{
	BlockIterator *iter = new BlockIterator(m, n, (m + 1) / 2, (n + 1) / 2);
	BlockMap *map = new MedianBlockMap(m, n);
	BlockProcess *process = new BlockProcess(iter, map, "Median Filter");
	return process;
}

SharedImageProcesser ProcessFactory::getMeanFilterProcess(int m, int n)
{
	BlockIterator *iter = new BlockIterator(m, n, (m + 1) / 2, (n + 1) / 2);
	BlockMap *map = new MeanBlockMap(m, n);
	BlockProcess *process = new BlockProcess(iter, map, "Median Filter");
	return process;
}


SharedProcess ProcessFactory::buildDynamicProcess(SharedImageProcesser processer)
{
	return new DynamicImageProcess(processer, tr("Dynamic Image Process"));
}

SharedProcess ProcessFactory::buildPreProcess(SharedImageProcesser processer)
{
	return new PreImageProcess(processer, tr("Pre Image Process"));
}

SharedProcess ProcessFactory::buildPostProcess(SharedImageProcesser processer)
{
	return new PostImageProcess(processer, tr("Post Image Process"));	
}
