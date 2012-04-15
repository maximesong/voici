#include "AlgebraicProcess.h"

#include <QImage>

#include "PixelIterator.h"
#include "ImagePixelMap.h"

#include "PreviewCanvas.h"

AlgebraicProcess::AlgebraicProcess(ImagePixelMap *map, const QString &processName)
	: ImageProcess(processName)
{
	setImagePixelMap(map);
	m_iter = new PixelIterator();
}

AlgebraicProcess::~AlgebraicProcess()
{
	delete m_map;
	delete m_iter;
}

void AlgebraicProcess::setImagePixelMap(ImagePixelMap *map)
{
	m_map = map;
}

void AlgebraicProcess::setPixelIterator(PixelIterator *iter)
{
	delete m_iter;
	m_iter = iter;
}

QImage AlgebraicProcess::produceProcessedImage(const QImage &image)
{
	QImage newImage = image;
	int width = qMin(image.width(), m_map->getWidth());
	int height = qMin(image.height(), m_map->getHeight());
	setPixelIterator(new PixelIterator(0, 0, width, height));
	m_iter->iterate(&newImage, m_map);
	return newImage;
}

