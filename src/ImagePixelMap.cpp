#include "ImagePixelMap.h"

int ImagePixelMap::getWidth()
{
	return m_image.width();
}

int ImagePixelMap::getHeight()
{
	return m_image.height();
}

void ImagePixelMap::setImage(const QImage &image)
{
	m_image = image;
}
