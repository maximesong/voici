#include "GrayImageCore.h"

#include "ProcessFactory.h"

GrayImageCore::GrayImageCore(const QString &id)
	: ImageCore(id)
{ 
	grayProcess = ProcessFactory::getStandardGrayProcess();
}

/*
GrayImageCore::GrayImageCore(const ImageCore &imageCore)
{
	m_current_image = imageCore.getCurrentImage();
	m_origin_image = imageCore.getOriginImage();
	m_id = imageCore.getId();
	m_processes = imageCore.get;
	m_current_process = imageCore.m_current_process;

}
*/

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
}
