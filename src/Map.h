#ifndef _MAP_H_
#define _MAP_H_

#include <QImage>

#include "AbstractMap.h"
#include "VoiciGlobal.h"
#include "Histogram.h"

uchar ensure_in_range(int byte);
uchar ensure_in_range(double byte);

class LinearByteMap : public ByteMap {
public:
	LinearByteMap(double k, double b);
	virtual uchar map(uchar src);
private:
	double m_k;
	double m_b;
};


class GrayRgbMap : public RgbMap {
public:
	GrayRgbMap(double rRate, double gRate, double bRate, double aRate);
	virtual QRgb map(uchar r, uchar g, uchar b, uchar a);
private:
	double m_r_rate;
	double m_g_rate;
	double m_b_rate;
	double m_a_rate;
};


class ImageBlendRgbMap : public PositionalRgbMap {
public:
	ImageBlendRgbMap(const QImage &image, double firstRate, double secondRate);
	virtual QRgb map(uchar r, uchar g, uchar b, uchar a, int x, int y);
private:
	double m_first_rate;
	double m_second_rate;
	QImage m_image;
};


class ImageProductRgbMap : public PositionalRgbMap {
public:
	ImageProductRgbMap(const QImage &image, double coefficient = 1.0);
	virtual QRgb map(uchar r, uchar g, uchar b, uchar a, int x, int y);
private:
	double m_coefficient;
	QImage m_image;
};


class ImageQuotientRgbMap : public PositionalRgbMap {
public:
	ImageQuotientRgbMap(const QImage &image, double coefficient = 1.0);
	virtual QRgb map(uchar r, uchar g, uchar b, uchar a, int x, int y);
private:
	double m_coefficient;
	QImage m_image;
};


class MatrixRgbMap : public AreaRgbMap {
public:
	MatrixRgbMap(int m, int n, const QVector<double> &matrix);
	virtual QRgb map(const QImage *image, int x, int y);
private:
	int m_m;
	int m_n;
	QVector<double> m_matrix;
};


class MeanRgbMap : public AreaRgbMap {
public:
	MeanRgbMap(int m, int n);
	virtual QRgb map(const QImage *image, int x, int y);
private:
	int m_m;
	int m_n;
};


class MedianRgbMap : public AreaRgbMap {
public:
	MedianRgbMap(int m, int n);
	virtual QRgb map(const QImage *image, int x, int y);
private:
	int m_m;
	int m_n;
};


class MidlevelNonlinearByteMap : public ByteMap {
public:
	MidlevelNonlinearByteMap(double c, double max);
	virtual uchar map(uchar src);
private:
	double m_c;
	double m_max;
};

class ThresholdRangeByteMap : public ByteMap {
public:
	ThresholdRangeByteMap(uchar low = 0, uchar high = MAX_PIXEL_VALUE);
	virtual uchar map(uchar src);
private:
	uchar m_low;
	uchar m_high;
};


class HistogramEqualizationByteMap : public ByteMap {
public:
	HistogramEqualizationByteMap(const QImage &image);
	void loadHistogram(const Histogram &histogram);
	virtual uchar map(uchar src);
private:
	int m_map[MAX_PIXEL_VALUE + 1];
};

#endif /* _MAP_H_ */
