#include "ProcessFactory.h"

#include "PixelMap.h"
#include "PixelProcess.h"
#include "ImageProcess.h"
#include "RatePixelMap.h"

ImageProcess *ProcessFactory::getStandardGrayProcess()
{
	PixelMap *map = new RatePixelMap(0.299, 0.587, 0.114);
	PixelProcess *process = new PixelProcess(map);
	return process;
}
