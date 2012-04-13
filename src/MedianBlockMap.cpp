#include "MedianBlockMap.h"

#include <iostream>
using namespace std;

MedianBlockMap::MedianBlockMap(int m, int n) {
	m_m = m;
	m_n = n;
}

QRgb MedianBlockMap::map(int x_offset, int y_offset, const QImage *image)
{
	int bytes = image->depth() / 8;
	const uchar *src = image->constBits();
	const uchar *xptr, *yptr;

	QVector<uchar> byte_array;
	QRgb rgb = 0;

	for (int byte = 0; byte != bytes; ++byte) {
		for (int j = y_offset; j != y_offset + m_n; ++j) {
			yptr = src + j * bytes * image->width();
			for (int i = x_offset; i != x_offset + m_m; ++i) {
				xptr = yptr + i * bytes + byte;
				byte_array.push_back(*xptr);
			}
		}
		qSort(byte_array);
		int median;
		if (byte_array.size() % 2 == 0)
			median = (int(byte_array[byte_array.size() / 2 - 1])	+ 
				  byte_array[byte_array.size() / 2]) / 2;
		else
			median = byte_array[byte_array.size() / 2];

		rgb |= median << (8 * byte);
		byte_array.clear();
	}

	return rgb;
}
