#include "ProcessFactory.h"

#include "PixelMap.h"
#include "PixelProcess.h"
#include "ImageProcess.h"
#include "RatePixelMap.h"
#include "RangeThresholdMap.h"

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
