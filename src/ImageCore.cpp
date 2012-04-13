#include "ImageCore.h"

#include "Exceptions.h"
#include "RatePixelMap.h"
#include "ProcessFactory.h"

#include <iostream>
using namespace std;


ImageCore::ImageCore(const QString &id)
	: QObject()
{
	m_id = id;
	m_current_process = -1;
}

ImageCore::ImageCore(const ImageCore &imageCore)
	: QObject()
{
	m_id = imageCore.getId();
	m_origin_image = imageCore.getOriginImage();
	m_current_image = imageCore.getCurrentImage();
	m_processes = imageCore.m_processes;
	m_current_process = imageCore.m_current_process;
	m_images_cache = imageCore.m_images_cache;
}


ImageCore &ImageCore::operator=(const ImageCore &imageCore)
{
	m_id = imageCore.getId();
	m_origin_image = imageCore.getOriginImage();
	m_current_image = imageCore.getCurrentImage();
	m_processes = imageCore.m_processes;
	m_images_cache = imageCore.m_images_cache;
	m_current_process = imageCore.m_current_process;

	return *this;
}


void ImageCore::load(const QString &filename)
{
	m_origin_image.load(filename);
	if (m_origin_image.isNull())
		throw FileError();

	/* This conversion is not efficient, to be improved */
	if (m_origin_image.format() != QImage::Format_ARGB32)
		m_origin_image = m_origin_image.convertToFormat(QImage::Format_ARGB32);


	Histogram histogram(m_origin_image);

	m_current_image = m_origin_image;
	m_processes.clear();
	m_images_cache.clear();
	m_current_process = -1;
	emit imageChanged(*this);
}


void ImageCore::pushImageProcess(ImageProcess *process)
{
	if ((m_current_process + 1) != m_processes.size()) {
		m_processes.remove(m_current_process + 1, 
				   m_processes.size() - m_current_process - 1);
		m_images_cache.remove(m_current_process + 1, 
				m_processes.size() - m_current_process - 1);
	}
	m_processes.push_back(QSharedPointer<ImageProcess>(process));
	++m_current_process;
	applyProcesses();
}

void ImageCore::updateImageProcess(ImageProcess *process)
{
	if ((m_current_process + 1) != m_processes.size()) {
		m_processes.remove(m_current_process + 1, 
				   m_processes.size() - m_current_process - 1);
		m_images_cache.remove(m_current_process + 1, 
				 m_processes.size() - m_current_process - 1);
	}
	if (m_processes.size() != 0) {
		m_processes.pop_back();
		m_images_cache.pop_back();
	}

	m_processes.push_back(QSharedPointer<ImageProcess>(process));
	++m_current_process;
	applyProcesses();
}

void ImageCore::clearImageProcess()
{
	m_processes.clear();
	m_images_cache.clear();
	m_current_process = -1;
	m_current_image = m_origin_image;
}


void ImageCore::goProcessN(int n)
{
	if (n < 0)
		n = m_processes.size() + n;
	if (n < m_processes.size()) {
		m_current_process = n;
		applyProcesses();
	}
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

void ImageCore::applyProcesses()
{
	applyPreProcesses();
	applyDynamicProcesses();
	applyPostProcesses();
	emit imageChanged(*this);
}

void ImageCore::setOriginImage(const QImage &image) {
	m_origin_image = image;
	m_processes.clear();
	m_images_cache.clear();
	m_current_process = -1;
	m_current_image = m_origin_image;
}

void ImageCore::applyDynamicProcesses()
{
	if (m_current_process < 0) {
		m_current_image = m_origin_image;
		return;
	}

	if (m_current_process < m_images_cache.size())
		m_current_image = m_images_cache[m_current_process];

	for (int i = m_images_cache.size(); i <= m_current_process; ++i) {
		applyImageProcess(m_processes[i].data());
		m_images_cache.push_back(m_current_image);
	}
}

void ImageCore::applyPostProcesses()
{
	/* empty */
}

void ImageCore::applyPreProcesses()
{
	/* empty */
}
