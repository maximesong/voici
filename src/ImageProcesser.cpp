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

RgbImageProcesser::RgbImageProcesser(Iterator *iter, PositionalRgbMap *map,
				     const QString &processerName  = "")
	: ImageProcesser(processName)
{
	m_iter = iter;
	m_map = map;
}

RgbImageProcesser::~RgbImageProcesser::()
{
	delete m_iter;
	delete m_map;
}

QImage RgbImageProcesser::produceProcessedImage(const QImage &src)
{
	QImage dest = image;
	m_iter(&dest, &src, m_map);
	return dest;
}


ByteImageProcesser::ByteImageProcesser(Iterator *iter, PositionalByteMap *map,
				     const QString &processerName  = "")
	: ImageProcesser(processName)
{
	m_iter = iter;
	m_map = map;
}

ByteImageProcesser::~ByteImageProcesser::()
{
	delete m_iter;
	delete m_map;
}

QImage ByteImageProcesser::produceProcessedImage(const QImage &src)
{
	QImage dest = image;
	m_iter(&dest, &src, m_map);
	return dest;
}


AreaRgbImageProcesser::AreaRgbImageProcesser(Iterator *iter, AreaRgbMap *map,
				     const QString &processerName  = "")
	: ImageProcesser(processName)
{
	m_iter = iter;
	m_map = map;
}

AreaRgbImageProcesser::~AreaRgbImageProcesser::()
{
	delete m_iter;
	delete m_map;
}

QImage AreaRgbImageProcesser::produceProcessedImage(const QImage &src)
{
	QImage dest = image;
	m_iter(&dest, &src, m_map);
	return dest;
}
