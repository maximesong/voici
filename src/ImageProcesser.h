#ifndef _IMAGEPROCESSER_H_
#define _IMAGEPROCESSER_H_

#include <QSharedPointer>
#include <QString>
#include <cmath>
#include <QLine>
#include <QRect>

#include "Map.h"
#include "Iterator.h"

class ImageProcesser {
public:
	ImageProcesser(const QString &processerName = "");

	void setProcesserName(const QString &name);

	QString getProcesserName() const;

	virtual QImage produceProcessedImage(const QImage &src) = 0;
private:
	QString m_processer_name;
};

typedef QSharedPointer<ImageProcesser> SharedImageProcesser;


class RgbImageProcesser : public ImageProcesser {
public:
	RgbImageProcesser(Iterator *iter, PositionalRgbMap *map,
			  const QString &processerName  = "");
	~RgbImageProcesser();
	virtual QImage produceProcessedImage(const QImage &src);
private:
	Iterator *m_iter;
	PositionalRgbMap *m_map;
};

class ByteImageProcesser : public ImageProcesser {
public:
	ByteImageProcesser(Iterator *iter, PositionalByteMap *map,
			  const QString &processerName  = "");
	~ByteImageProcesser();
	virtual QImage produceProcessedImage(const QImage &src);
private:
	Iterator *m_iter;
	PositionalByteMap *m_map;
};

class AreaRgbImageProcesser : public ImageProcesser {
public:
	AreaRgbImageProcesser(AreaIterator *iter, AreaRgbMap *map,
			  const QString &processerName  = "");
	~AreaRgbImageProcesser();
	virtual QImage produceProcessedImage(const QImage &src);
private:
	AreaIterator *m_iter;
	AreaRgbMap *m_map;
};

class QuickGaussBlurProcesser : public ImageProcesser {
public:
	QuickGaussBlurProcesser(double horizontal, double vertical);
	virtual QImage produceProcessedImage(const QImage &image);
private:
	QImage gauss_iir(const QImage &image);

	void find_iir_constants(double std_dev);
	static void transfer_pixels (const double *src1, const double *src2,
				     uchar *dest, int bytes, int width);
	double n_p[5];
	double n_m[5];
	double bd_p[5];
	double bd_m[5];
	double d_p[5];
	double d_m[5];
	double vert;
	double horz;
};

class BilinearScaleProcesser : public ImageProcesser {
public:
	BilinearScaleProcesser(int width, int height);
	virtual QImage produceProcessedImage(const QImage &image);
private:
	int m_width;
	int m_height;
};

class NearestNeighbourScaleProcesser : public ImageProcesser {
public:
	NearestNeighbourScaleProcesser(int width, int height);
	virtual QImage produceProcessedImage(const QImage &image);
private:
	int m_width;
	int m_height;
};

class NearestNeighbourRotateProcesser : public ImageProcesser {
public:
	NearestNeighbourRotateProcesser(double rotateAngle);
	virtual QImage produceProcessedImage(const QImage &image);
private:
	int m_width;
	int m_height;
	double m_rotate_angle;
};


class DrawPolygonProcesser : public ImageProcesser {
public:
	DrawPolygonProcesser(QVector<QPoint> points);
	virtual QImage produceProcessedImage(const QImage &image);
private:
	QVector<QPoint> m_points;
};

class DrawEllipseProcesser : public ImageProcesser {
public:
	DrawEllipseProcesser(int cx, int cy, int rx, int ry);
	virtual QImage produceProcessedImage(const QImage &image);
private:
	int m_cx;
	int m_cy;
	int m_rx;
	int m_ry;
};

#endif /* _IMAGEPROCESSER_H_ */
