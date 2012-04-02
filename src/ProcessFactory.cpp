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

ImageProcess *ProcessFactory::getLinearProcess(int k, int b)
{
	PixelMap *map = new LinearPixelMap(k, b);
	return buildFromPixelMap(map);
}

ImageProcess *ProcessFactory::getMidlevelNonlinearMap(int c, int max_level)
{
	PixelMap *map = new LinearPixelMap(c, max_level);
	return buildFromPixelMap(map);
}

