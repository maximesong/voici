#include "Map.h"

uchar ensure_in_range(int byte)
{
	if (byte < 0)
		return 0;
	else if (byte > MAX_PIXEL_VALUE)
		return MAX_PIXEL_VALUE;
	
	return uchar(byte);
}

uchar ensure_in_range(double byte)
{
	return ensure_in_range(int(byte));
}

LinearByteMap::LinearByteMap(double k, double b)
{
	m_k = k;
	m_b = b;
}

uchar LinearByteMap::map(uchar src)
{
	return ensure_in_range(m_k * src + m_b);
}

GrayRgbMap::GrayRgbMap(double rRate, double gRate, double bRate, double aRate)
{
	m_r_rate = rRate;
	m_g_rate = gRate;
	m_b_rate = bRate;
	m_a_rate = aRate;
}

QRgb GrayRgbMap::map(uchar r, uchar g, uchar b, uchar a)
{
	uchar gray = ensure_in_range(r * m_r_rate + g * m_g_rate + b * m_b_rate);
	uchar alpha = ensure_in_range(a * m_a_rate);
	return qRgba(gray, gray, gray, alpha);
}


ImageBlendRgbMap::ImageBlendRgbMap(const QImage &image, 
				   double firstRate, double secondRate)
{
	m_first_rate = firstRate;
	m_second_rate = secondRate;
	m_image = image;
}

QRgb ImageBlendRgbMap::map(uchar r, uchar g, uchar b, uchar a, int x, int y)
{
	if (! m_image.valid(x, y))
		return qRgba(r, g, b, a);

	QRgb rgb = m_image.pixel(x, y);
	uchar blend_r = ensure_in_range(r * m_first_rate + 
					qRed(rgb) * m_second_rate);
	uchar blend_g = ensure_in_range(g * m_first_rate + 
					qGreen(rgb) * m_second_rate);
	uchar blend_b = ensure_in_range(b * m_first_rate + 
					qBlue(rgb) * m_second_rate);
	uchar blend_a = ensure_in_range(a * m_first_rate + 
					qAlpha(rgb) * m_second_rate);

	return qRgba(blend_r, blend_g, blend_b, blend_a);
}


ImageProductRgbMap::ImageProductRgbMap(const QImage &image, double coefficient)
{
	m_coefficient = coefficient;
	m_image = image;
}


QRgb ImageProductRgbMap::map(uchar r, uchar g, uchar b, uchar a, int x, int y)
{
	if (! m_image.valid(x, y))
		return qRgba(r, g, b, a);

	QRgb rgb = m_image.pixel(x, y);
	uchar product_r = ensure_in_range(m_coefficient * r * qRed(rgb));
	uchar product_g = ensure_in_range(m_coefficient * g * qGreen(rgb));
	uchar product_b = ensure_in_range(m_coefficient * b * qBlue(rgb));
	/* not multiply the two alpha chanels*/

	return qRgba(product_r, product_g, product_b, a);
}

ImageQuotientRgbMap::ImageQuotientRgbMap(const QImage &image, double coefficient)
{
	m_coefficient = coefficient;
	m_image = image;
}


QRgb ImageQuotientRgbMap::map(uchar r, uchar g, uchar b, uchar a, int x, int y)
{
	if (! m_image.valid(x, y))
		return qRgba(r, g, b, a);

	QRgb rgb = m_image.pixel(x, y);
	uchar quotient_r = ensure_in_range(m_coefficient * r / qRed(rgb));
	uchar quotient_g = ensure_in_range(m_coefficient * g / qGreen(rgb));
	uchar quotient_b = ensure_in_range(m_coefficient * b / qBlue(rgb));
	/* not divide the two alpha chanels*/

	return qRgba(quotient_r, quotient_g, quotient_b, a);
}

MatrixRgbMap::MatrixRgbMap(int m, int n, const QVector<double> &matrix)
{
	m_m = m;
	m_n = n;
	m_matrix = matrix;
}

QRgb MatrixRgbMap::map(const QImage *image, int x, int y)
{
	int bytes = image->depth() / 8;
	int start_byte = 0;
	int end_byte = bytes;
	if (bytes == 4) {
		start_byte = 0;
		end_byte = 3;
	}

	const uchar *src = image->constBits();
	const uchar *x_ptr;
	const uchar *y_ptr;

	double sum = 0;
	QRgb rgb = qRgb(0, 0, 0);

	for (int byte = start_byte; byte != end_byte; ++byte) {
		for (int j = 0; j != m_n; ++j) {
			y_ptr = src + (y + j) * bytes * image->width();
			for (int i = 0; i != m_m; ++i) {
				x_ptr = y_ptr + (x + i) * bytes  + byte;
				sum += (*x_ptr) * m_matrix[i + j * m_m];
			}
		}
		rgb |= int(ensure_in_range(sum)) << (8 * byte);
		sum = 0;
	}
		
	return rgb;
}


MeanRgbMap::MeanRgbMap(int m, int n)
{
	m_m = m;
	m_n = n;
}

QRgb MeanRgbMap::map(const QImage *image, int x, int y)
{
	int bytes = image->depth() / 8;
	const uchar *src = image->constBits();
	const uchar *xptr, *yptr;

	const int byte_block_size = m_m * m_n;
	QRgb rgb = 0;

	for (int byte = 0; byte != bytes; ++byte) {
		int byte_sum = 0;
		for (int j = y; j != y + m_n; ++j) {
			yptr = src + j * bytes * image->width();
			for (int i = x; i != x + m_m; ++i) {
				xptr = yptr + i * bytes + byte;
				byte_sum += (*xptr);
			}
		}
		uchar mean = byte_sum / byte_block_size;
		rgb |= int(mean) << (8 * byte);
	}

	return rgb;
}



MedianRgbMap::MedianRgbMap(int m, int n) {
	m_m = m;
	m_n = n;
}

QRgb MedianRgbMap::map(const QImage *image, int x, int y)
{
	int bytes = image->depth() / 8;
	const uchar *src = image->constBits();
	const uchar *xptr, *yptr;

	QVector<uchar> byte_array;
	QRgb rgb = 0;

	for (int byte = 0; byte != bytes; ++byte) {
		for (int j = y; j != y + m_n; ++j) {
			yptr = src + j * bytes * image->width();
			for (int i = x; i != x + m_m; ++i) {
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

MidlevelNonlinearByteMap::MidlevelNonlinearByteMap(double c, double max)
{
	m_c = c;
	m_max = max;
}


uchar MidlevelNonlinearByteMap::map(uchar src)
{
	return ensure_in_range(src + m_c * src * (m_max - src));
}

ThresholdRangeByteMap::ThresholdRangeByteMap(uchar low, uchar high)
{
	m_low = low;
	m_high = high;
}

uchar ThresholdRangeByteMap::map(uchar src)
{
	if (src >= m_low && src <= m_high)
		return 255;
	else
		return 0;
}
