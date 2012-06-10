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


// #define SCALE_WIDTH     150

// #define HORIZONTAL        0
// #define VERTICAL          1
// #define SUPERSAMPLE       3
// #define MAG_THRESHOLD     7.5
// #define COUNT_THRESHOLD   0.1
// #define MAX_POINTS        12

// typedef enum
// {
//   SQUARES   = 0,
//   HEXAGONS  = 1,
//   OCTAGONS  = 2,
//   TRIANGLES = 3
// } TileType;

// #define SMOOTH   0
// #define ROUGH    1

// #define BW       0
// #define FG_BG    1

// typedef struct
// {
//   double x, y;
// } Vertex;

// typedef struct
// {
//   uint  npts;
//   Vertex pts[MAX_POINTS];
// } Polygon;

// typedef struct
// {
//   double base_x, base_y;
//   double norm_x, norm_y;
//   double light;
// } SpecVec;

// typedef struct
// {
//   double  tile_size;
//   double  tile_height;
//   double  tile_spacing;
//   double  tile_neatness;
//   bool tile_allow_split;
//   double  light_dir;
//   double  color_variation;
//   boolean antialiasing;
//   int     color_averaging;
//   TileType tile_type;
//   int     tile_surface;
//   int     grout_color;
// } MosaicVals;

// class MosaicProcesser : public ImageProcesser {
// public:
// 	MosaicProcesser();
// 	virtual QImage produceProcessedImage(const QImage &image);
// private:
// 	QImage mosaic(const QImage &image);
// 	void find_gradients();
// 	void find_max_gradient();
// 	void gaussian_deriv();
// 	void make_curve();
// 	void make_curved();
// 	void grid_localize();
// 	void grid_render();
// 	void polygon_add_point (Polygon *poly, gdouble  x, gdouble  y);
// 	void polygon_reset (Polygon *poly);

// 	void fill_poly_image (Polygon      *poly,
// 			      QImage *image,
// 					       double       vary,
// 					       int          x1,
// 					       int          y1,
// 					       int          x2,
// 					       int          y2,
// 					       uchar       *dest);

// 	static void find_poly_dir (Polygon *poly, uchar  *m_gr,
// 				   uchar  *h_gr, uchar  *v_gr,
// 				   double *dir, double *loc,
// 				   int x1, int y1,
// 				   int x2, int y2);
// 	static void clip_point (double *dir, double *pt,
// 				double  x1, double  y1,
// 				double  x2, double  y2,
// 				Polygon *poly_new);

// 	static void grid_create_squares(int x1, int y1, int x2, int y2);
// 	static void grid_create_hexagons(int x1, int y1, int x2, int y2);
// 	static void grid_create_octagons(int x1, int y1, int x2, int y2);
// 	static void grid_create_triangles(int x1, int y1, int x2, int y2);

// 	uchar *m_h_grad;
// 	uchar *m_v_grad;
// 	uchar *m_m_grad;
// 	MosaicVals m_mvals;
// 	gdouble  std_dev = 1.0;
// 	gdouble  light_x;
// 	gdouble  light_y;
// 	gdouble  scale;
// 	gint     grid_rows;
// 	gint     grid_cols;
// 	gint     grid_row_pad;
// 	gint     grid_col_pad;
// 	gint     grid_multiple;
// 	gint     grid_rowstride;
// 	guchar   back[4];
// 	guchar   fore[4];
// 	SpecVec  vecs[MAX_POINTS];

// };

class MultiProcesser : public ImageProcesser {
public:
	MultiProcesser(QVector<ImageProcesser*> processers);
	~MultiProcesser();
	virtual QImage produceProcessedImage(const QImage &image);
private:
	QVector<ImageProcesser*> m_processers;
};

class MorphoDistanceProcesser : public ImageProcesser {
public:
	/* no support for area operation at this time */
	MorphoDistanceProcesser();
	~MorphoDistanceProcesser();
	virtual QImage produceProcessedImage(const QImage &image);
private:
	ImageProcesser *m_erosion_processer;
};


class MorphoSkeletonProcesser : public ImageProcesser {
public:
	MorphoSkeletonProcesser();
	~MorphoSkeletonProcesser();
	virtual QImage produceProcessedImage(const QImage &image);
private:
	ImageProcesser *getOpenProcesser();
	ImageProcesser *getErosionProcesser();
	ImageProcesser *m_open_processer;
	ImageProcesser *m_erosion_processer;
};

#endif /* _IMAGEPROCESSER_H_ */
