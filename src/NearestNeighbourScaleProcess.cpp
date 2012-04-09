#include "NearestNeighbourScaleProcess.h"

#include <QImage>

NearestNeighbourScaleProcess::NearestNeighbourScaleProcess(int width, int height)
	: ScaleProcess(width, height)
{
	/* empty */
}

QImage NearestNeighbourScaleProcess::generateNewImage(const QImage &image)
{
	double x_scale = ((double) m_width) / image.width();
	double y_scale = ((double) m_height) / image.height();

        /* calculate the maped coordinate in advance to avoid repeating */
	int x_map[m_width];
	int y_map[m_height];

	for (int i = 0; i != m_width; ++i)
		x_map[i] = (int) (i / x_scale);


	for (int i = 0; i != m_height; ++i)
		y_map[i] = (int) (i / y_scale);

	QImage new_image = QImage(m_width, m_height, QImage::Format_ARGB32);
	
	int bytes = new_image.depth() / 8;

	const uchar *src = image.constBits();
	uchar *dest = new_image.bits();

	const uchar *ps;
	uchar *pd;
	
	for (int j = 0; j != m_height; ++j) {
		ps = src + y_map[j] * bytes * image.width();
		pd = dest + j * bytes * m_width;
		for (int i = 0; i != m_width; ++i) {
			memcpy(pd + bytes * i, ps + bytes * x_map[i], bytes);
		}
	}

	return new_image;
}
