#include "MeanBlockMap.h"

#include <iostream>
using namespace std;

MeanBlockMap::MeanBlockMap(int m, int n)
{
	m_m = m;
	m_n = n;
}

QRgb MeanBlockMap::map(int x_offset, int y_offset, QImage *image)
{
	int bytes = image->depth() / 8;
	const uchar *src = image->constBits();
	const uchar *xptr, *yptr;

	const int byte_block_size = m_m * m_n;
	QRgb rgb = 0;

	for (int byte = 0; byte != bytes; ++byte) {
		int byte_sum = 0;
		for (int j = y_offset; j != y_offset + m_n; ++j) {
			yptr = src + j * bytes * image->width();
			for (int i = x_offset; i != x_offset + m_m; ++i) {
				xptr = yptr + i * bytes + byte;
				byte_sum += (*xptr);
			}
		}
		uchar mean = byte_sum / byte_block_size;
		rgb |= int(mean) << (8 * byte);
	}

	return rgb;
}
