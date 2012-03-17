#ifndef _PROCESSFACTORY_H_
#define _PROCESSFACTORY_H_

class ImageProcess;

class ProcessFactory {
public:
	ProcessFactory();
	static ImageProcess *getStandardGrayProcess();
};

#endif /* _PROCESSFACTORY_H_ */
