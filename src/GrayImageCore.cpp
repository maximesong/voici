#include "GrayImageCore.h"

#include "ProcessFactory.h"

GrayImageCore::GrayImageCore(const QString &id)
	: ImageCore(id)
{ 
	grayProcess = ProcessFactory::getStandardGrayProcess();
	binaryProcess = ProcessFactory::getBinaryProcess();
}


GrayImageCore::~GrayImageCore()
{
	delete grayProcess;
}


void GrayImageCore::setColorfulImage(const ImageCore& imageCore)
{
	ImageCore &thisImageCore = *this;
	thisImageCore = imageCore;
	thisImageCore = imageCore;
	grayProcess->processImage(this);
	currentToOrigin();
}

void GrayImageCore::setThreshold(int low, int high)
{
	delete binaryProcess;
	binaryProcess = ProcessFactory::getBinaryProcess(low, high);
	applyProcesses();
}

void GrayImageCore::applyPostProcesses()
{
	if (binaryProcess != 0)
		applyImageProcess(binaryProcess);
}

void GrayImageCore::applyPreProcesses()
{
	/*
	if (grayProcess != 0)
		applyImageProcess(grayProcess);
	*/
}
