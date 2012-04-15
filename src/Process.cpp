#include "Process.h"

#include "ImageFamily.h"

ImageFamilyProcess::ImageFamilyProcess(const QString &processName)
{
	setProcessName(processName);
}

void ImageFamilyProcess::setProcessName(const QString &name)
{
	m_process_name = name;
}

QString ImageFamilyProcess::getProcessName() const
{
	return m_process_name;
}

DynamicImageProcess::DynamicImageProcess(SharedImageProcessor imageProcesser,
					 const QString &processName)
	: ImageFamilyProcess(processName)
{
	m_image_processer = imageProcesser;
}

void DynamicImageProcess::applyToImageFamily(ImageFamily *imageFamily)
{
	imageFamily->pushDynamicImageProcesser(m_image_processer);
}

PreImageProcess::PreImageProcess(PreProcesser id, SharedImageProcessor imageProcesser,
				 const QString &processName = "")
{
	m_id = id;
	setPreProcesser(imageProcesser);
}

void PreImageProcess::applyToImageFamily(ImageFamily *imageFamily)
{
	imageFamily->setPreProcesser(m_image_processer);
}

void PreImageProcess::setPreProcesser(PreProcesser id, SharedImageProcesser processer)
{
	m_image_processer = processer;
}

PostImageProcess::PostImageProcess(PostProcesser id, SharedImageProcessor imageProcesser,
				 const QString &processName = "")
{
	m_id = id;
	setPostProcesser(imageProcesser);
}

void PostImageProcess::applyToImageFamily(ImageFamily *imageFamily)
{
	imageFamily->setPostProcesser(m_image_processer);
}

void PostImageProcess::setPostProcesser(PostProcesser id, SharedImageProcesser processer)
{
	m_image_processer = processer;
}
