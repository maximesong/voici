#include "Process.h"

#include "ImageFamily.h"

ImageFamilyProcess::ImageFamilyProcess(const QString &processName)
{
	setProcessName(processName);
}

void ImageFamilyProcess::setProcessName(const QString name)
{
	m_process_name = name;
}

QString ImageFamilyProcess::getProcessName() const
{
	return m_process_name;
}




DynamicImageProcess::DynamicImageProcess(SharedImageProcessor imageProcessor,
					 const QString &processName)
	: ImageFamilyProcess(processName)
{
	m_image_processer = imageProcessor;
}

void DynamicImageProcess::applyToImageFamily(ImageFamily *imageFamily)
{
	imageFamily->pushDynamicImageProcesser(m_image_processer);
}
