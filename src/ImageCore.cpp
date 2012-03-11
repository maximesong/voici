#include "ImageCore.h"
#include "Exceptions.h"

ImageCore::ImageCore()
{
	histogram = 0;
}

ImageCore::~ImageCore()
{
	delete histogram;
}


void ImageCore::load(const QString &filename)
{
	m_image.load(filename);
	if (m_image.isNull)
		throw FileError();

	emit imageChanged();
}
