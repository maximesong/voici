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

DynamicImageProcess::DynamicImageProcess(SharedImageProcesser imageProcesser,
					 const QString &processName)
{
	m_image_processer = imageProcesser;
	setProcessName(processName);
}

void DynamicImageProcess::applyToImageFamily(ImageFamily *imageFamily)
{
	imageFamily->pushDynamicImageProcesser(m_image_processer);
}

SharedImageProcesser DynamicImageProcess::getProcesser()
{
	return m_image_processer;
}

PreImageProcess::PreImageProcess(PreProcesser id, 
				 SharedImageProcesser imageProcesser,
				 const QString &processName)
{
	setPreProcesser(id, imageProcesser);
	setProcessName(processName);
}

void PreImageProcess::applyToImageFamily(ImageFamily *imageFamily)
{
	imageFamily->setPreProcesser(m_id, m_image_processer);
}

void PreImageProcess::setPreProcesser(PreProcesser id, SharedImageProcesser processer)
{
	m_id = id;
	m_image_processer = processer;
}

PostImageProcess::PostImageProcess(PostProcesser id, 
				   SharedImageProcesser imageProcesser,
				   const QString &processName)
{
	setPostProcesser(id, imageProcesser);
	setProcessName(processName);
}

void PostImageProcess::applyToImageFamily(ImageFamily *imageFamily)
{
	imageFamily->setPostProcesser(m_id, m_image_processer);
}

void PostImageProcess::setPostProcesser(PostProcesser id, SharedImageProcesser processer)
{
	m_id = id;
	m_image_processer = processer;
}


