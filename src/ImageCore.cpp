#include "ImageCore.h"

#include "Exceptions.h"
#include "RatePixelMap.h"
#include "ProcessFactory.h"

ImageCore::ImageCore(const QString &id)
{
	m_id = id;
}

ImageCore::ImageCore(const ImageCore &imageCore)
{
	m_id = imageCore.getId();
	m_origin_image = imageCore.getOriginImage();
	m_current_image = imageCore.getCurrentImage();
}

ImageCore::~ImageCore()
{
	/* empty */
}

ImageCore &ImageCore::operator=(const ImageCore &imageCore)
{
	m_id = imageCore.getId();
	m_origin_image = imageCore.getOriginImage();
	m_current_image = imageCore.getCurrentImage();
}


void ImageCore::load(const QString &filename)
{
	m_origin_image.load(filename);
	if (m_origin_image.isNull())
		throw FileError();
	
	m_current_image = m_origin_image;
	m_processes.clear();
	emit imageChanged(*this);
}


void ImageCore::pushImageProcess(ImageProcess *process)
{
	if (m_current_process != m_processes.size())
		m_processes.remove(m_current_process + 1, 
				   m_processes.size() - m_current_process - 1);
	m_processes.push_back(QSharedPointer<ImageProcess>(process));
}

void ImageCore::goProcessN(int n)
{
	if (n < 0)
		n = m_processes.size() + n;
	if (n < m_processes.size())
		m_current_process = n;
}

ImageCore ImageCore::toGrayImageCore(const ImageCore &imageCore)
{
	ImageCore grayImageCore = ImageCore(imageCore);
	ImageProcess *process = ProcessFactory::getStandardGrayProcess();
	grayImageCore.applyImageProcess(process);
	grayImageCore.currentToOrigin();
	return grayImageCore;
}

void ImageCore::applyImageProcess(ImageProcess *process)
{
	process->processImage(this);
}
