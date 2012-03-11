#include <QPainter>

#include "Histogram.h"

Histogram::Histogram()
{
	rRate = 11 / 32;
	gRate = 16 / 32;
	bRate = 5 / 32;
}

void Histogram::computeHistogram(const QImage &image)
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
			++gray_histogram[r * rRate + g * gRate + b * bRate];
		}
}


void Histogram::setBlendRate(double r, double g, double b)
{
	rRate = r;
	gRate = g;
	bRate = b;
}
