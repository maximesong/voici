#include "ImageBlendMap.h"

#include <QImage>

#include "ImageBlendMapPolicy.h"

ImageBlendMap::ImageBlendMap(const QImage &image, ImageBlendMapPolicy *policy)
{
	setImage(image);
	m_policy = policy;
}

ImageBlendMap::~ImageBlendMap()
{
	delete m_policy;
}

void ImageBlendMap::setPolicy(ImageBlendMapPolicy *policy)
{
	delete m_policy;
	m_policy = policy;
}

QRgb ImageBlendMap::map(int x, int y, const QImage &image)
{
	QRgb rgb = image.pixel(x, y);
	return map(x, y, qRed(rgb), qGreen(rgb), qBlue(rgb));
}

QRgb ImageBlendMap::map(int x, int y, int r, int g, int b)
{
	QRgb rgb = m_image.pixel(x, y);
	double new_r = qRed(rgb);
	double new_g = qGreen(rgb);
	double new_b = qBlue(rgb);

	int blend_r = m_policy->channelBlend(r, new_r);
	int blend_g = m_policy->channelBlend(g, new_g);
	int blend_b = m_policy->channelBlend(b, new_b);
	return qRgb(blend_r, blend_g, blend_b);
}
