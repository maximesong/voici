#include "ImageBlendMap.h"

#include <QImage>

ImageBlendMap::ImageBlendMap(const QImage &image, 
			     double origin_rate, double new_rate)
{
	setImage(image);
	setBlendRate(origin_rate, new_rate);
}

void ImageBlendMap::setBlendRate(double origin_rate, double new_rate)
{
	m_origin_rate = origin_rate;
	m_new_rate = new_rate;
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

	int blend_r = safe_range(m_origin_rate * r + m_new_rate * new_r);
	int blend_g = safe_range(m_origin_rate * g + m_new_rate * new_g);
	int blend_b = safe_range(m_origin_rate * b + m_new_rate * new_b);
	return qRgb(blend_r, blend_g, blend_b);
}
