#include "ImageCore.h"
#include "Exceptions.h"

ImageCore::ImageCore(const QString &name)
{
	m_name = name;
}


ImageCore::~ImageCore()
{
	/* empty */
}


void ImageCore::load(const QString &filename)
{
	m_image.load(filename);
	if (m_image.isNull())
		throw FileError();

	emit imageChanged(*this);
}
