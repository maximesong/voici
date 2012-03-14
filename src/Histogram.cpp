#include <QImage>

#include "Histogram.h"

Histogram::Histogram(const QImage &image, double rRate, 
		     double gRate,  double bRate)
{
	for (int i = 0; i != 255; ++i) {
		r_histogram[i] = 0;
		g_histogram[i] = 0;
		b_histogram[i] = 0;
		gray_histogram[i] = 0;
	}

	for (int i = 0; i != image.width(); ++i)
		for (int j = 0; j != image.height(); ++j) {
			QRgb rgb = image.pixel(i, j);
			int r = qRed(rgb);
			int g = qGreen(rgb);
			int b = qBlue(rgb);
			++r_histogram[r];
			++g_histogram[g];
			++b_histogram[b];
			++gray_histogram[int(r * rRate + g * gRate + b * bRate)];
		}
}
