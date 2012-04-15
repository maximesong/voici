#include "ProcessFactory.h"

#include "Map.h"
#include "Iterator.h"
#include "VoiciGlobal.h"


SharedProcess ProcessFactory::getStandardGrayProcess(IteratorArea *area)
{
	Iterator *iter = new Iterator(area);
	RgbMap *map = new GrayRgbMap(0.299, 0.587, 0.114, 1);
	RgbImageProcesser *processer = 
		new RgbImageProcesser(iter, map, tr("Graying"));
	return buildPreProcess(Graying, SharedImageProcesser(processer));
}


SharedProcess ProcessFactory::getBinaryProcess(int low, int high,
					       IteratorArea *area)
{
	Iterator *iter = new Iterator(area);
	ByteMap *map = new ThresholdRangeByteMap(low, high);
	ByteImageProcesser *processer = 
		new ByteImageProcesser(iter, map, tr("Thredshold"));
	return buildDynamicProcess(SharedImageProcesser(processer));
}



SharedProcess ProcessFactory::getConvolutionProcess(int rows, int columns,
						    int centerRow, 
						    int centerColumn,
						    const QVector<double> &matrix,
						    IteratorArea *area)
{
	AreaIterator *iter = 
		new AreaIterator(rows, columns, centerRow, centerColumn, area);
	AreaRgbMap *map = new MatrixRgbMap(rows, columns, matrix);
	AreaRgbImageProcesser *processer = 
		new AreaRgbImageProcesser(iter, map, tr("Convolution"));
	return buildDynamicProcess(SharedImageProcesser(processer));
}

SharedProcess ProcessFactory::getLinearProcess(double k, double b,
					       IteratorArea *area)
{
	Iterator *iter = new Iterator(area);
	ByteMap *map = new LinearByteMap(k, b);
	ByteImageProcesser *processer = 
		new ByteImageProcesser(iter, map, tr("Linear Process"));
	return buildDynamicProcess(SharedImageProcesser(processer));
}

SharedProcess ProcessFactory::getMidlevelNonlinearMap(double c, double max,
						      IteratorArea *area)
{
	Iterator *iter = new Iterator(area);
	ByteMap *map = new MidlevelNonlinearByteMap(c, max);
	ByteImageProcesser *processer = 
		new ByteImageProcesser(iter, map, tr("Midlevel Nonlinear"));
	return buildDynamicProcess(SharedImageProcesser(processer));
}

SharedProcess ProcessFactory::getImageLinearBlendProcess(const QImage &image,
							 double rate1, 
							 double rate2,
							 IteratorArea *area)
{
	Iterator *iter = new Iterator(area);
	PositionalRgbMap *map = new ImageBlendRgbMap(image, rate1, rate2);
	RgbImageProcesser *processer = 
		new RgbImageProcesser(iter, map, tr("Image Linear Blend"));
	return buildDynamicProcess(SharedImageProcesser(processer));
}

SharedProcess ProcessFactory::getImageProductProcess(const QImage &image,
						     double coefficient,
						     IteratorArea *area)
{
	Iterator *iter = new Iterator(area);
	PositionalRgbMap *map = new ImageProductRgbMap(image, coefficient);
	RgbImageProcesser *processer = 
		new RgbImageProcesser(iter, map, tr("Image Product"));
	return buildDynamicProcess(SharedImageProcesser(processer));
}

SharedProcess ProcessFactory::getImageQuotientProcess(const QImage &image,
						      double coefficient,
						      IteratorArea *area)
{
	Iterator *iter = new Iterator(area);
	PositionalRgbMap *map = new ImageQuotientRgbMap(image, coefficient);
	RgbImageProcesser *processer = 
		new RgbImageProcesser(iter, map, tr("Image Product"));
	return buildDynamicProcess(SharedImageProcesser(processer));
}

SharedProcess ProcessFactory::getQuickGaussBlurProcess(double horz, double vert)
{
	ImageProcesser *processer = new QuickGaussBlurProcesser(horz, vert);
	return buildDynamicProcess(SharedImageProcesser(processer));
}

SharedProcess ProcessFactory::getBilinearScaleProcess(int width, int height)
{
	ImageProcesser *processer = new BilinearScaleProcesser(width, height);
	return buildDynamicProcess(SharedImageProcesser(processer));
}

SharedProcess ProcessFactory::getNearestNeighbourScaleProcess(int width, 
							      int height)
{
	ImageProcesser *processer = new NearestNeighbourScaleProcesser(width, height);
	return buildDynamicProcess(SharedImageProcesser(processer));
}

SharedProcess ProcessFactory::getNearestNeighbourRotateProcess(double rotateAngle)
{
	ImageProcesser *processer = new NearestNeighbourRotateProcesser(rotateAngle);
	return buildDynamicProcess(SharedImageProcesser(processer));
}

SharedProcess ProcessFactory::getMedianFilterProcess(int m, int n,
						     IteratorArea *area)
{
	AreaIterator *iter = 
		new AreaIterator(m, n, (m + 1) / 2, (n + 1) / 2, area);
	AreaRgbMap *map = new MedianRgbMap(m, n);
	AreaRgbImageProcesser *processer = 
		new AreaRgbImageProcesser(iter, map, tr("Median Filter"));
	return buildDynamicProcess(SharedImageProcesser(processer));
}

SharedProcess ProcessFactory::getMeanFilterProcess(int m, int n, 
						   IteratorArea *area)
{
	AreaIterator *iter = 
		new AreaIterator(m, n, (m + 1) / 2, (n + 1) / 2, area);
	AreaRgbMap *map = new MeanRgbMap(m, n);
	AreaRgbImageProcesser *processer = 
		new AreaRgbImageProcesser(iter, map, tr("Mean Filter"));
	return buildDynamicProcess(SharedImageProcesser(processer));
}


SharedProcess ProcessFactory::buildDynamicProcess(SharedImageProcesser processer)
{
	ImageFamilyProcess *process = 
		new DynamicImageProcess(processer, tr("Dynamic Image Process"));
	return SharedProcess(process);
}

SharedProcess ProcessFactory::buildPreProcess(PreProcesser id,
					      SharedImageProcesser processer)
{
	ImageFamilyProcess *process = 
		new PreImageProcess(id, processer, tr("Pre Image Process"));
	return SharedProcess(process);
}

SharedProcess ProcessFactory::buildPostProcess(PostProcesser id,
					       SharedImageProcesser processer)
{
	ImageFamilyProcess *process = 
		new PostImageProcess(id, processer, tr("Post Image Process"));	
	return SharedProcess(process);
}
