#ifndef _PROCESSFACTORY_H_
#define _PROCESSFACTORY_H_

#include "VoiciGlobal.h"

class ImageProcess;
class PixelMap;

class ProcessFactory {
public:
	ProcessFactory();
	static ImageProcess *getStandardGrayProcess();
	static ImageProcess *getBinaryProcess(int low = 0, 
						 int high = MAX_PIXEL_VALUE);
private:
	static ImageProcess *buildFromPixelMap(PixelMap *map);
};

#endif /* _PROCESSFACTORY_H_ */
