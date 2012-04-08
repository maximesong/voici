#include "ImageUtility.h"

#include <assert.h>
#include <string.h>


void ImageUtility::getRow(const QImage &image, uchar *buf,
			  int x, int y, int width)
{
	assert(buf != 0);
	assert(x >= 0 && x + width <= image.width());
	assert(y >= 0 && y < image.height());
	assert(width > 0);

	int bytes = image.depth() / 8;
	const uchar *row = image.constBits() + bytes * (image.width() * y  + x);

	memcpy(buf, row, width * bytes);
}

void ImageUtility::getColumn(const QImage &image, uchar *buf,
				    int x, int y, int height)
{
	assert(buf != 0);
	assert(x >= 0 && x < image.width());
	assert(y >= 0 && y + height <= image.height());
	assert(height > 0);

	int bytes = image.depth() / 8;
	const uchar *column = image.constBits() + bytes * (image.width() * y  + x);
	int offset = bytes * image.width();

	for (int i = 0; i != height; ++i) {
		memcpy(buf, column, bytes);
		column += offset;
		buf += bytes;
	}
}

void ImageUtility::setRow(QImage &image, const uchar *buf,
				 int x, int y, int width)
{
	assert(buf != 0);
	assert(x >= 0 && x + width <= image.width());
	assert(y >= 0 && y < image.height());
	assert(width > 0);

	int bytes = image.depth() / 8;
	uchar *row = image.bits() + bytes * (image.width() * y  + x);

	memcpy(row, buf, width * bytes);
}

void ImageUtility::setColumn(QImage &image, const uchar *buf,
				    int x, int y, int height)
{
	assert(buf != 0);
	assert(x >= 0 && x < image.width());
	assert(y >= 0 && y + height <= image.height());
	assert(height > 0);

	int bytes = image.depth() / 8;
	uchar *column = image.bits() + bytes * (image.width() * y  + x);
	int offset = bytes * image.width();

	for (int i = 0; i != height; ++i) {
		memcpy(column, buf, bytes);
		column += offset;
		buf += bytes;
	}
}
