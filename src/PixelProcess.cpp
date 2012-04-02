#include "PixelProcess.h"

#include <QImage>

#include "PixelIterator.h"
#include "PixelMap.h"

PixelProcess::PixelProcess(PixelMap *map, const QString &processName)
	: ImageProcess(processName)
{
	m_map = map;
	m_iter = new PixelIterator();
}

PixelProcess::~PixelProcess()
{
	delete m_map;
	delete m_iter;
}

QImage PixelProcess::generateNewImage(const QImage &image)
{
	QImage newImage = image;
	m_iter->iterate(&newImage, m_map);
	return newImage;
}

void PixelProcess::setPixelMap(PixelMap *map)
{
	delete m_map;
	m_map = map;
}

void PixelProcess::setIterator(PixelIterator *iter)
{
	delete m_iter;
	m_iter = iter;
}
