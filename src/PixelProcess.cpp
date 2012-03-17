#include "PixelProcess.h"

#include <QImage>

#include "PixelIterator.h"
#include "PixelMap.h"

PixelProcess::PixelProcess(PixelMap *map)
{
	m_map = map;
}

PixelProcess::~PixelProcess()
{
	delete m_map;
}

QImage PixelProcess::generateNewImage(const QImage &image)
{
	QImage newImage = image;
	PixelIterator::iterate(&newImage, m_map);
	return newImage;
}
