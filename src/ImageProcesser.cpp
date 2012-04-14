#include "ImageProcesser.h"

#include <QImage>

ImageProcesser::ImageProcesser(const QString &processerName)
{
	setProcesserName(processerName);
}

void ImageProcesser::setProcesserName(const QString &name)
{
	m_processer_name = name;
}

QString ImageProcesser::getProcesserName() const
{
	return m_processer_name;
}

