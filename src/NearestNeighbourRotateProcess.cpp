#include "NearestNeighbourRotateProcess.h"

#include <cmath>
#include <iostream>
using namespace std;

#include <QImage>

#include "VoiciGlobal.h"

NearestNeighbourRotateProcess::NearestNeighbourRotateProcess(double rotateAngle)
	: RotateProcess(rotateAngle)
{
	/* empty */
}

QImage NearestNeighbourRotateProcess::generateNewImage(const QImage &image)
{
	double sinA = sin(counter_clock_rotate_angle / 180 * PI);
	double cosA = cos(counter_clock_rotate_angle / 180 * PI);

	int new_length = sqrt(image.width() * image.width() + 
			      image.height() *image.height());

	double rx = new_length / 2;
	double ry = new_length / 2;

	double x_diff = (new_length - image.width()) / 2;
	double y_diff = (new_length - image.height()) / 2;

	QImage new_image = QImage(new_length, new_length, QImage::Format_ARGB32);

	int bytes = new_image.depth() / 8;

	const uchar *src = image.constBits();
	uchar *dest = new_image.bits();
	const uchar *ps;
	uchar *pd;

	uchar transparent[] = { 255, 255, 255, 0 };
 
	double const_x = -rx * cosA + ry * sinA + rx;
	double const_y = -rx * sinA - ry * cosA + ry;

	for (int j = 0; j < new_image.height(); ++j) {
		for (int i = 0; i < new_image.height(); ++ i) {
			int x = i * cosA - j * sinA + const_x - x_diff;
			int y = i * sinA + j * cosA + const_y - y_diff;
			if (image.valid(x, y))
				ps = src + (x + y * image.width()) * bytes;
			else
				ps = transparent;
			pd = dest + (i + j * new_image.width()) * bytes;
			memcpy(pd, ps, bytes);
		}
	}

	return new_image;
}