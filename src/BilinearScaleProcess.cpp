#include "BilinearScaleProcess.h"

#include <QImage>

const int  BILINEAR_SHIFT = 4;

BilinearScaleProcess::BilinearScaleProcess(int width, int height)
	: ScaleProcess(width, height)
{
	/* empty */
}

/* 
 * shift some float values into integer before calculation and shift 
 * them back to avoid the expensive float operation.
 */
QImage BilinearScaleProcess::generateNewImage(const QImage &image)
{
	double x_scale = ((double) m_width) / image.width();
	double y_scale = ((double) m_height) / image.height();

	/* calculate values in advance to avoid repeating */
	int x_map[m_width];
	int left_interv_shifted[m_width];
	int right_interv_shifted[m_width];

	int y_map[m_height];
	int up_interv_shifted[m_height];
	int down_interv_shifted[m_height];

	for (int i = 0; i != m_width; ++i) {
		double x = i / x_scale;
		x_map[i] = int(x);
		left_interv_shifted[i] = (x - x_map[i]) * (1 << BILINEAR_SHIFT);
		right_interv_shifted[i] = (1 << BILINEAR_SHIFT) - 
			left_interv_shifted[i];
	}

	for (int i = 0; i != m_height; ++i) {
		double y = (i / y_scale);
		y_map[i] = int(y);
		down_interv_shifted[i] = (y - y_map[i]) * (1 << BILINEAR_SHIFT);
		up_interv_shifted[i] = (1 << BILINEAR_SHIFT) - down_interv_shifted[i];
	}

	QImage new_image = QImage(m_width, m_height, QImage::Format_ARGB32);
	
	int bytes = new_image.depth() / 8;

	const uchar *src = image.constBits();
	uchar *dest = new_image.bits();

	const uchar *ps;
	uchar *pd;
	uchar x0y0, x1y0, x0y1, x1y1;

	for (int j = 0; j != m_height; ++j) {
		ps = src + y_map[j] * bytes * image.width();
		pd = dest + j * bytes * m_width;
		for (int i = 0; i != m_width; ++i) {
			for (int k = 0; k != bytes; ++k) {
				x0y0 = *(ps + x_map[i] * bytes + k);
				x0y1 = *(ps + (x_map[i] + image.width()) * bytes + k);
				x1y0 = *(ps + (x_map[i] + 1) * bytes + k);
				x1y1 = *(ps + (x_map[i] + 1 + image.width()) * bytes + k);
				uchar result = ((x0y0 * right_interv_shifted[i] +
						 x1y0 * left_interv_shifted[i]) *
						up_interv_shifted[j] +
						(x0y1 * right_interv_shifted[i] +
						 x1y1 * left_interv_shifted[i]) *
						down_interv_shifted[j]) 
					>> (2 * BILINEAR_SHIFT);
				*(pd + bytes * i + k) = result;
			}
		}
	}

	return new_image;
}
