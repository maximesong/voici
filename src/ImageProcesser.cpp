#include "ImageProcesser.h"

#include <QImage>
#include <QPainter>
#include <QPen>
#include <QLinearGradient>
#include "ImageUtility.h"

ImageProcesser::ImageProcesser(const QString &processerName)
{
	setProcesserName(processerName);
}

void ImageProcesser::setProcesserName(const QString &name)
{
	m_processer_name = name;
}

QString ImageProcesser::getProcesserName() const
{
	return m_processer_name;
}

RgbImageProcesser::RgbImageProcesser(Iterator *iter, PositionalRgbMap *map,
				     const QString &processerName)
	: ImageProcesser(processerName)
{
	m_iter = iter;
	m_map = map;
}

RgbImageProcesser::~RgbImageProcesser()
{
	delete m_iter;
	delete m_map;
}

QImage RgbImageProcesser::produceProcessedImage(const QImage &src)
{
	QImage dest = src;
	m_iter->rgbIterate(&dest, &src, m_map);
	return dest;
}


ByteImageProcesser::ByteImageProcesser(Iterator *iter, PositionalByteMap *map,
				       const QString &processerName)
	: ImageProcesser(processerName)
{
	m_iter = iter;
	m_map = map;
}

ByteImageProcesser::~ByteImageProcesser()
{
	delete m_iter;
	delete m_map;
}

QImage ByteImageProcesser::produceProcessedImage(const QImage &src)
{
	QImage dest = src;
	m_iter->byteIterate(&dest, &src, m_map);
	return dest;
}


AreaRgbImageProcesser::AreaRgbImageProcesser(AreaIterator *iter, AreaRgbMap *map,
					     const QString &processerName)
	: ImageProcesser(processerName)
{
	m_iter = iter;
	m_map = map;
}

AreaRgbImageProcesser::~AreaRgbImageProcesser()
{
	delete m_iter;
	delete m_map;
}

QImage AreaRgbImageProcesser::produceProcessedImage(const QImage &src)
{
	QImage dest = src;
	m_iter->areaIterate(&dest, &src, m_map);
	return dest;
}


QuickGaussBlurProcesser::QuickGaussBlurProcesser(double horizontal, double vertical)
{
	vert = vertical;
	horz = horizontal;
}

QImage QuickGaussBlurProcesser::produceProcessedImage(const QImage &image)
{
	return gauss_iir(image);
}

/* 
 * This function comes from gimp, blur-gauss.c, and it is slightly changed
 * in the coding style to make the coding style of the project consistant 
 */
void QuickGaussBlurProcesser::find_iir_constants(double std_dev)
{
	/*  The constants used in the implemenation of a casual sequence
	 *  using a 4th order approximation of the gaussian operator
	 */

	const double div = sqrt (2 * PI) * std_dev;
	const double x0 = -1.783 / std_dev;
	const double x1 = -1.723 / std_dev;
	const double x2 = 0.6318 / std_dev;
	const double x3 = 1.997  / std_dev;
	const double x4 = 1.6803 / div;
	const double x5 = 3.735 / div;
	const double x6 = -0.6803 / div;
	const double x7 = -0.2598 / div;
	int i;

	n_p[0] = x4 + x6;
	n_p[1] = (exp(x1)*(x7*sin(x3)-(x6+2*x4)*cos(x3)) +
		  exp(x0)*(x5*sin(x2) - (2*x6+x4)*cos(x2)));
	n_p[2] = (2 * exp(x0+x1) *
		  ((x4+x6)*cos(x3)*cos(x2) - x5*cos(x3)*sin(x2) -
		   x7*cos(x2)*sin(x3)) +
		  x6*exp(2*x0) + x4*exp(2*x1));
	n_p[3] = (exp(x1+2*x0) * (x7*sin(x3) - x6*cos(x3)) +
		  exp(x0+2*x1) * (x5*sin(x2) - x4*cos(x2)));
	n_p[4] = 0.0;

	d_p[0] = 0.0;
	d_p[1] = -2 * exp(x1) * cos(x3) -  2 * exp(x0) * cos (x2);
	d_p[2] = 4 * cos(x3) * cos(x2) * exp(x0 + x1) +  exp(2 * x1) + exp(2 * x0);
	d_p[3] = -2 * cos(x2) * exp(x0 + 2*x1) -  2*cos(x3) * exp(x1 + 2*x0);
	d_p[4] = exp(2*x0 + 2*x1);

	for (i = 0; i <= 4; i++)
		d_m[i] = d_p[i];

	n_m[0] = 0.0;

	for (i = 1; i <= 4; i++)
		n_m[i] = n_p[i] - d_p[i] * n_p[0];

	{
		double sum_n_p, sum_n_m, sum_d;
		double a, b;

		sum_n_p = 0.0;
		sum_n_m = 0.0;
		sum_d = 0.0;

		for (i = 0; i <= 4; i++) {
			sum_n_p += n_p[i];
			sum_n_m += n_m[i];
			sum_d += d_p[i];
		}

		a = sum_n_p / (1.0 + sum_d);
		b = sum_n_m / (1.0 + sum_d);

		for (i = 0; i <= 4; i++) {
			bd_p[i] = d_p[i] * a;
			bd_m[i] = d_m[i] * b;
		}
	}
}



/* 
 * This function comes from gimp, blur-gauss.c. Some code is removed,
 * some code is chnanged to fit the QImage structure, and the coding style
 * is modified to fit this project 
 */
QImage QuickGaussBlurProcesser::gauss_iir(const QImage &image)
{
	QImage dest_image = image;
	int bytes;
//	int has_alpha;
	uchar *dest;
	uchar *src, *sp_p, *sp_m;
	double *val_p = 0;
	double *val_m = 0;
	double *vp, *vm;
	int i, j;
	int row, col, b;
	int terms;
	int initial_p[4];
	int initial_m[4];
	double std_dev;

	int x1 = 0;
	int y1 = 0;
	int height = image.height();
	int width = image.width();

	bytes = image.depth() / 8;
//	has_alpha = 0;

	val_p = new double[qMax(width, height) * bytes];
	val_m = new double[qMax(width, height) * bytes];

	src =  new uchar[qMax(width, height) * bytes];
	dest = new uchar[qMax(width, height) * bytes];

/*  First the vertical pass  */
	if (vert > 0.0)
	{
		if (vert < 0)
			vert = -vert;
		vert += 1.0;
		std_dev = sqrt (-(vert * vert) / (2 * log(1.0 / 255.0)));

		/*  derive the constants for calculating the gaussian
		 *  from the std dev
		 */

		find_iir_constants (std_dev);

		for (col = 0; col < width; col++)
		{
			memset(val_p, 0, height * bytes * sizeof (double));
			memset(val_m, 0, height * bytes * sizeof (double));

			ImageUtility::getColumn(image, src, col + x1, y1, height);

/*
  if (has_alpha)
  multiply_alpha (src, height, bytes);
*/

			sp_p = src;
			sp_m = src + (height - 1) * bytes;
			vp = val_p;
			vm = val_m + (height - 1) * bytes;

			/*  Set up the first vals  */
			for (i = 0; i < bytes; i++)
			{
				initial_p[i] = sp_p[i];
				initial_m[i] = sp_m[i];
			}

			for (row = 0; row < height; row++)
			{
				double *vpptr, *vmptr;
				terms = (row < 4) ? row : 4;

				for (b = 0; b < bytes; b++)
				{
					vpptr = vp + b; vmptr = vm + b;
					for (i = 0; i <= terms; i++)
					{
						*vpptr += n_p[i] * sp_p[(-i * bytes) + b] - d_p[i] * vp[(-i * bytes) + b];
						*vmptr += n_m[i] * sp_m[(i * bytes) + b] - d_m[i] * vm[(i * bytes) + b];
					}
					for (j = i; j <= 4; j++)
					{
						*vpptr += (n_p[j] - bd_p[j]) * initial_p[b];
						*vmptr += (n_m[j] - bd_m[j]) * initial_m[b];
					}
				}

				sp_p += bytes;
				sp_m -= bytes;
				vp += bytes;
				vm -= bytes;
			}

			transfer_pixels (val_p, val_m, dest, bytes, height);

/*
  if (has_alpha)
  separate_alpha (dest, height, bytes);
*/
			ImageUtility::setColumn(dest_image, dest, 
						col + x1, y1, height);

		}
	}

/*  Now the horizontal pass  */
	if (horz > 0.0)
	{
		if (horz < 0)
			horz = -horz;
		horz += 1.0;

		if (horz != vert)
		{
			std_dev = sqrt (-(horz * horz) / (2 * log (1.0 / 255.0)));

			/*  derive the constants for calculating the gaussian
			 *  from the std dev
			 */
			find_iir_constants (std_dev);
		}


		for (row = 0; row < height; row++)
		{

			memset (val_p, 0, width * bytes * sizeof (double));
			memset (val_m, 0, width * bytes * sizeof (double));

			ImageUtility::getRow(dest_image, src, x1, row + y1, width);
/*
  if (has_alpha)
  multiply_alpha (src, width, bytes);
*/

			sp_p = src;
			sp_m = src + (width - 1) * bytes;
			vp = val_p;
			vm = val_m + (width - 1) * bytes;

			/*  Set up the first vals  */
			for (i = 0; i < bytes; i++)
			{
				initial_p[i] = sp_p[i];
				initial_m[i] = sp_m[i];
			}

			for (col = 0; col < width; col++)
			{
				double *vpptr, *vmptr;

				terms = (col < 4) ? col : 4;

				for (b = 0; b < bytes; b++)
				{
					vpptr = vp + b; vmptr = vm + b;

					for (i = 0; i <= terms; i++)
					{
						*vpptr += n_p[i] * sp_p[(-i * bytes) + b] -
							d_p[i] * vp[(-i * bytes) + b];
						*vmptr += n_m[i] * sp_m[(i * bytes) + b] -
							d_m[i] * vm[(i * bytes) + b];
					}
					for (j = i; j <= 4; j++)
					{
						*vpptr += (n_p[j] - bd_p[j]) * initial_p[b];
						*vmptr += (n_m[j] - bd_m[j]) * initial_m[b];
					}
				}

				sp_p += bytes;
				sp_m -= bytes;
				vp += bytes;
				vm -= bytes;
			}

			transfer_pixels(val_p, val_m, dest, bytes, width);

/*
  if (has_alpha)
  separate_alpha (dest, width, bytes);
*/
			ImageUtility::setRow(dest_image, dest, 
					     x1, row + y1, width);
		}
	}

/*  free up buffers  */

	delete [] val_p;
	delete [] val_m;

	delete [] src;
	delete [] dest;

	return dest_image;
}

/* 
 * This function comes from gimp, blur-gauss.c, and it is slightly changed
 * in the coding style to make the coding style of the project consistant 
 */
void QuickGaussBlurProcesser::transfer_pixels (const double *src1, 
					       const double *src2,
					       uchar *dest, int bytes,
					       int width)
{
	int    b;
	int    bend = bytes * width;
	double sum;

	for (b = 0; b < bend; b++) {
		sum = *src1++ + *src2++;

		if (sum > 255)
			sum = 255;
		else if (sum < 0)
			sum = 0;

		*dest++ = (uchar) sum;
	}
}


NearestNeighbourScaleProcesser::NearestNeighbourScaleProcesser(int width, 
							       int height)
{
	m_width = width;
	m_height = height;
}

QImage NearestNeighbourScaleProcesser::produceProcessedImage(const QImage &image)
{
	double x_scale = ((double) m_width) / image.width();
	double y_scale = ((double) m_height) / image.height();

        /* calculate the maped coordinate in advance to avoid repeating */
	int x_map[m_width];
	int y_map[m_height];

	for (int i = 0; i != m_width; ++i)
		x_map[i] = (int) (i / x_scale);


	for (int i = 0; i != m_height; ++i)
		y_map[i] = (int) (i / y_scale);

	QImage new_image = QImage(m_width, m_height, QImage::Format_ARGB32);
	
	int bytes = new_image.depth() / 8;

	const uchar *src = image.constBits();
	uchar *dest = new_image.bits();

	const uchar *ps;
	uchar *pd;
	
	for (int j = 0; j != m_height; ++j) {
		ps = src + y_map[j] * bytes * image.width();
		pd = dest + j * bytes * m_width;
		for (int i = 0; i != m_width; ++i) {
			memcpy(pd + bytes * i, ps + bytes * x_map[i], bytes);
		}
	}

	return new_image;
}

BilinearScaleProcesser::BilinearScaleProcesser(int width, int height)
{
	m_width = width;
	m_height = height;
}

/* 
 * shift some float values into integer before calculation and shift 
 * them back to avoid the expensive float operation.
 */
QImage BilinearScaleProcesser::produceProcessedImage(const QImage &image)
{
	double x_scale = ((double) m_width) / image.width();
	double y_scale = ((double) m_height) / image.height();

	/* calculate values in advance to avoid repeating */
	int x_map[m_width];
	int left_interv_shifted[m_width];
	int right_interv_shifted[m_width];

	int y_map[m_height];
	int up_interv_shifted[m_height];
	int down_interv_shifted[m_height];

	for (int i = 0; i != m_width; ++i) {
		double x = i / x_scale;
		x_map[i] = int(x);
		left_interv_shifted[i] = (x - x_map[i]) * (1 << BILINEAR_SHIFT);
		right_interv_shifted[i] = (1 << BILINEAR_SHIFT) - 
			left_interv_shifted[i];
	}

	for (int i = 0; i != m_height; ++i) {
		double y = (i / y_scale);
		y_map[i] = int(y);
		down_interv_shifted[i] = (y - y_map[i]) * (1 << BILINEAR_SHIFT);
		up_interv_shifted[i] = (1 << BILINEAR_SHIFT) - down_interv_shifted[i];
	}

	QImage new_image = QImage(m_width, m_height, QImage::Format_ARGB32);
	
	int bytes = new_image.depth() / 8;

	const uchar *src = image.constBits();
	uchar *dest = new_image.bits();

	const uchar *ps;
	uchar *pd;
	uchar x0y0, x1y0, x0y1, x1y1;

	for (int j = 0; j != m_height; ++j) {
		ps = src + y_map[j] * bytes * image.width();
		pd = dest + j * bytes * m_width;
		for (int i = 0; i != m_width; ++i) {
			for (int k = 0; k != bytes; ++k) {
				x0y0 = *(ps + x_map[i] * bytes + k);
				x0y1 = *(ps + (x_map[i] + image.width()) * bytes + k);
				x1y0 = *(ps + (x_map[i] + 1) * bytes + k);
				x1y1 = *(ps + (x_map[i] + 1 + image.width()) * bytes + k);
				uchar result = ((x0y0 * right_interv_shifted[i] +
						 x1y0 * left_interv_shifted[i]) *
						up_interv_shifted[j] +
						(x0y1 * right_interv_shifted[i] +
						 x1y1 * left_interv_shifted[i]) *
						down_interv_shifted[j]) 
					>> (2 * BILINEAR_SHIFT);
				*(pd + bytes * i + k) = result;
			}
		}
	}

	return new_image;
}


NearestNeighbourRotateProcesser::NearestNeighbourRotateProcesser(double rotateAngle)
{
	m_rotate_angle = rotateAngle;
}

QImage NearestNeighbourRotateProcesser::produceProcessedImage(const QImage &image)
{
	double sinA = sin(m_rotate_angle / 180 * PI);
	double cosA = cos(m_rotate_angle / 180 * PI);

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

DrawPolygonProcesser::DrawPolygonProcesser(QVector<QPoint> points)
{
	m_points = points;
}

QImage DrawPolygonProcesser::produceProcessedImage(const QImage &image)
{
	QImage dest = image;
	QPainter *painter = new QPainter(&dest);
	QLinearGradient linearGrad(QPointF(0, 0), QPointF(5, 5));
	linearGrad.setColorAt(0, Qt::black);
	linearGrad.setColorAt(1, Qt::white);
	linearGrad.setSpread(QGradient::RepeatSpread);
	QPen pen(QBrush(linearGrad),
		 2,
		 Qt::DashLine);
	painter->setPen(pen);
	painter->drawPolygon(m_points);
	delete painter;
	return dest;
}


DrawEllipseProcesser::DrawEllipseProcesser(int cx, int cy, int rx, int ry)
{
	m_cx = cx;
	m_cy = cy;
	m_rx = rx;
	m_ry = ry;
}

QImage DrawEllipseProcesser::produceProcessedImage(const QImage &image)
{
	QImage dest = image;
	QPainter *painter = new QPainter(&dest);
	QLinearGradient linearGrad(QPointF(0, 0), QPointF(5, 5));
	linearGrad.setColorAt(0, Qt::black);
	linearGrad.setColorAt(1, Qt::white);
	linearGrad.setSpread(QGradient::RepeatSpread);
	QPen pen(QBrush(linearGrad),
		 2,
		 Qt::DashLine);
	painter->setPen(pen);
	painter->drawEllipse(QPoint(m_cx, m_cy), m_rx, m_ry);
	delete painter;
	return dest;
}

// QImage MosaicProcesser::mosaic(const QImage &image)
// {
// 	int x1, y1, x2, y2;
// 	int width, height;
// 	int alpha;
// 	GimpRGB color;

// 	QImage new_image = image;

// 	x1 = 0;
// 	y1 = 0;
// 	x2 = x1 + image.width();
// 	y2 = y1 + image.height();

// 	/*  Find the gradients  */
// 	find_gradients (image, std_dev, x1, y1, width, height);


// /*  Create the tile geometry grid  */
// 	switch (m_mvals.tile_type)
// 	{
// 	case SQUARES:
// 		grid_create_squares (x1, y1, x2, y2);
// 		break;
// 	case HEXAGONS:
// 		grid_create_hexagons (x1, y1, x2, y2);
// 		break;
// 	case OCTAGONS:
// 		grid_create_octagons (x1, y1, x2, y2);
// 		break;
// 	case TRIANGLES:
// 		grid_create_triangles(x1, y1, x2, y2);
// 		break;
// 	default:
// 		break;
// 	}

// 	/*  Deform the tiles based on image content  */
// 	grid_localize (x1, y1, x2, y2);

// 	switch (mvals.grout_color)
// 	{
// 	case BW:
// 		fore[0] = fore[1] = fore[2] = 255;
// 		back[0] = back[1] = back[2] = 0;
// 		break;

// 	case FG_BG:
// 		gimp_context_get_foreground (&color);
// 		gimp_drawable_get_color_uchar (drawable->drawable_id, &color, fore);

// 		gimp_context_get_background (&color);
// 		gimp_drawable_get_color_uchar (drawable->drawable_id, &color, back);
// 		break;
// 	}
// /* alpha to be changed */  
// 	alpha = 0; 

// 	light_x = -cos (mvals.light_dir * G_PI / 180.0);
// 	light_y =  sin (mvals.light_dir * G_PI / 180.0);
// 	scale = (mvals.tile_spacing > mvals.tile_size / 2.0) ?
// 		0.5 : 1.0 - mvals.tile_spacing / mvals.tile_size;

// 	grid_render (drawable, x1, y1, x2, y2, preview);
// }

// void MosaicProcesser::find_gradients()
// {
// 	GimpPixelRgn src_rgn;
// 	GimpPixelRgn dest_rgn;
// 	int bytes;
// 	int i, j;
// 	uchar *gr, *dh, *dv;
// 	int hmax, vmax;
// 	int row, rows;
// 	int ith_row;

// 	rows = width * 2 + height * 2;
// 	ith_row = rows / 256;
// 	if (!ith_row)
// 		ith_row = 1;
// 	row = 0;

// 	gaussian_deriv (&src_rgn, &dest_rgn,
// 			HORIZONTAL, std_dev, &row, rows, ith_row,
// 			x1, y1, x1 + width, y1 + height, preview);

// 	dest_rgn.x = dest_rgn.y = 0;
// 	dest_rgn.w = width;
// 	dest_rgn.h = height;
// 	dest_rgn.bpp = 1;
// 	dest_rgn.rowstride = width;
// 	dest_rgn.data = h_grad;
// 	find_max_gradient (&src_rgn, &dest_rgn);

// 	gaussian_deriv (&src_rgn, &dest_rgn,
// 			VERTICAL, std_dev, &row, rows, ith_row,
// 			x1, y1, x1 + width, y1 + height, preview);

// 	dest_rgn.x = dest_rgn.y = 0;
// 	dest_rgn.w = width;
// 	dest_rgn.h = height;
// 	dest_rgn.bpp = 1;
// 	dest_rgn.rowstride = width;
// 	dest_rgn.data = v_grad;
// 	find_max_gradient (&src_rgn, &dest_rgn);

// 	/*  fill in the gradient map  */
// 	gr = m_grad;
// 	dh = h_grad;
// 	dv = v_grad;

// 	for (i = 0; i < height; i++)
// 	{
// 		for (j = 0; j < width; j++, dh++, dv++, gr++)
// 		{
// 			/*  Find the gradient  */
// 			if (!j || !i || (j == width - 1) || (i == height - 1))
// 			{
// 				*gr = MAG_THRESHOLD;
// 			}
// 			else
// 			{
// 				hmax = *dh - 128;
// 				vmax = *dv - 128;

// 				*gr = (uchar) sqrt(hmax * hmax + vmax * vmax);
// 			}
// 		}
// 	}
// }


// void MosaicProcesser::gaussian_deriv(const QImage *src_image,
// 				     QImage *dest_image)
// {
// 	uchar *dest, *dp;
// 	uchar *src, *sp, *s;
// 	uchar *data;
// 	int *buf, *b;
// 	int chan;
// 	int i, row, col;
// 	int start, end;
// 	int curve_array [9];
// 	int sum_array [9];
// 	int *curve;
// 	int *sum;
// 	int bytes;
// 	int val;
// 	int total;
// 	int length;
// 	int initial_p[4], initial_m[4];

// 	bytes = src_image->depth() / 8;
// 	length = qMax(src_rgn->w, src_rgn->h) * bytes;
// 	data = new uchar[length * 2];
// 	src = data;
// 	dest = data + length;

// #ifdef UNOPTIMIZED_CODE
// 	length = 3;    /*  static for speed  */
// #else
// 	/* badhack :) */
// # define length 3
// #endif

// 	/*  initialize  */
// 	curve = curve_array + length;
// 	sum = sum_array + length;
// 	buf = new int[qMax((x2 - x1), (y2 - y1)) * bytes];

// 	if (type == VERTICAL)
// 	{
// 		make_curve_d(curve, sum, std_dev, length);
// 		total = sum[0] * -2;
// 	}
// 	else
// 	{
// 		make_curve(curve, sum, std_dev, length);
// 		total = sum[length] + curve[length];
// 	}

// 	for (col = x1; col < x2; col++)
// 	{
// 		ImageUtility::getColumn(src_image, src, col, y1, (y2 - y1));

// 		sp = src;
// 		dp = dest;
// 		b = buf;

// 		for (chan = 0; chan < bytes; chan++)
// 		{
// 			initial_p[chan] = sp[chan];
// 			initial_m[chan] = sp[(y2 - y1 - 1) * bytes + chan];
// 		}

// 		for (row = y1; row < y2; row++)
// 		{
// 			start = ((row - y1) < length) ? (y1 - row) : -length;
// 			end = ((y2 - row - 1) < length) ? (y2 - row - 1) : length;

// 			for (chan = 0; chan < bytes; chan++)
// 			{
// 				s = sp + (start * bytes) + chan;
// 				val = 0;
// 				i = start;

// 				if (start != -length)
// 					val += initial_p[chan] * (sum[start] - sum[-length]);

// 				while (i <= end)
// 				{
// 					val += *s * curve[i++];
// 					s += bytes;
// 				}

// 				if (end != length)
// 					val += initial_m[chan] * (sum[length] + curve[length] - sum[end+1]);

// 				*b++ = val / total;
// 			}

// 			sp += bytes;
// 		}

// 		b = buf;
// 		if (type == VERTICAL)
// 			for (row = y1; row < y2; row++)
// 			{
// 				for (chan = 0; chan < bytes; chan++)
// 				{
// 					b[chan] += 128;
// 					dp[chan] = CLAMP0255 (b[chan]);
// 				}
// 				b += bytes;
// 				dp += bytes;
// 			}
// 		else
// 			for (row = y1; row < y2; row++)
// 			{
// 				for (chan = 0; chan < bytes; chan++)
// 				{
// 					dp[chan] = CLAMP0255 (b[chan]);
// 				}
// 				b += bytes;
// 				dp += bytes;
// 			}

// 		ImageUtility::setColumn(dest_image, dest, col, y1, (y2 - y1));
// 	}

// 	if (type == HORIZONTAL)
// 	{
// 		make_curve_d (curve, sum, std_dev, length);
// 		total = sum[0] * -2;
// 	}
// 	else
// 	{
// 		make_curve (curve, sum, std_dev, length);
// 		total = sum[length] + curve[length];
// 	}

// 	for (row = y1; row < y2; row++)
// 	{
// 		ImageUtility::getRow(dest_image, src, x1, row, (x2 - x1));

// 		sp = src;
// 		dp = dest;
// 		b = buf;

// 		for (chan = 0; chan < bytes; chan++)
// 		{
// 			initial_p[chan] = sp[chan];
// 			initial_m[chan] = sp[(x2 - x1 - 1) * bytes + chan];
// 		}

// 		for (col = x1; col < x2; col++)
// 		{
// 			start = ((col - x1) < length) ? (x1 - col) : -length;
// 			end = ((x2 - col - 1) < length) ? (x2 - col - 1) : length;

// 			for (chan = 0; chan < bytes; chan++)
// 			{
// 				s = sp + (start * bytes) + chan;
// 				val = 0;
// 				i = start;

// 				if (start != -length)
// 					val += initial_p[chan] * (sum[start] - sum[-length]);

// 				while (i <= end)
// 				{
// 					val += *s * curve[i++];
// 					s += bytes;
// 				}

// 				if (end != length)
// 					val += initial_m[chan] * (sum[length] + curve[length] - sum[end+1]);

// 				*b++ = val / total;
// 			}

// 			sp += bytes;
// 		}

// 		b = buf;
// 		if (type == HORIZONTAL)
// 			for (col = x1; col < x2; col++)
// 			{
// 				for (chan = 0; chan < bytes; chan++)
// 				{
// 					b[chan] += 128;
// 					dp[chan] = CLAMP0255 (b[chan]);
// 				}
// 				b += bytes;
// 				dp += bytes;
// 			}
// 		else
// 			for (col = x1; col < x2; col++)
// 			{
// 				for (chan = 0; chan < bytes; chan++)
// 				{
// 					dp[chan] = CLAMP0255 (b[chan]);
// 				}
// 				b += bytes;
// 				dp += bytes;
// 			}

// 		ImageUtility::setRow(dest_rgn, dest, x1, row, (x2 - x1));
// 	}

// 	delete buf;
// 	delete data;
// #ifndef UNOPTIMIZED_CODE
// 	/* end bad hack */
// #undef length
// #endif

// }

// void MosaicProcesser::grid_localize (int x1, int y1, int x2, int y2)
// {
// 	int     width, height;
// 	int     i, j;
// 	int     k, l;
// 	int     x3, y3, x4, y4;
// 	int     size;
// 	int     max_x, max_y;
// 	int     max;
// 	uchar  *data;
// 	double  rand_localize;
// 	Vertex  *pt;

// 	width  = x2 - x1;
// 	height = y2 - y1;
// 	size = (int) m_mvals.tile_size;
// 	rand_localize = size * (1.0 - mvals.tile_neatness);

// 	for (i = -grid_row_pad; i < grid_rows + grid_row_pad; i++)
// 		for (j = -grid_col_pad * grid_multiple; j < (grid_cols + grid_col_pad) * grid_multiple; j++)
// 		{
// 			pt = grid + (i * grid_rowstride + j);

// 			max_x = pt->x + (int) (fp_rand (rand_localize) - rand_localize/2.0);
// 			max_y = pt->y + (int) (fp_rand (rand_localize) - rand_localize/2.0);

// 			x3 = pt->x - (int) (rand_localize / 2.0);
// 			y3 = pt->y - (int) (rand_localize / 2.0);
// 			x4 = x3 + (int) rand_localize;
// 			y4 = y3 + (int) rand_localize;

// 			x3 = CLAMP (x3, x1, x2 - 1);
// 			y3 = CLAMP (y3, y1, y2 - 1);
// 			x4 = CLAMP (x4, x1, x2 - 1);
// 			y4 = CLAMP (y4, y1, y2 - 1);

// 			max = *(m_grad + (y3 - y1) * width + (x3 - x1));
// 			data = m_grad + width * (y3 - y1);

// 			for (k = y3; k <= y4; k++)
// 			{
// 				for (l = x3; l <= x4; l++)
// 				{
// 					if (data[l - x1] > max)
// 					{
// 						max_y = k;
// 						max_x = l;
// 						max = data[l - x1];
// 					}
// 				}
// 				data += width;
// 			}

// 			pt->x = max_x;
// 			pt->y = max_y;
// 		}
// }

// double MosaicProcesser::fp_rand (double val)
// {
// 	return (rand()/(double)RAND_MAX) * val; 
// }

// int MosaicProcesser::random_int_range(int start, int end)
// {
// 	return start + (rand() % (end - start));
// }

// void MosaicProcesser::grid_render (GimpDrawable *drawable,
// 				   int          x1,
// 				   int          y1,
// 				   int          x2,
// 				   int          y2)
// {
// 	GimpPixelRgn  src_rgn;
// 	int          i, j, k;
// 	uchar       *dest = NULL, *d;
// 	uchar        col[4];
// 	int          bytes;
// 	int          size, frac_size;
// 	int          count;
// 	int          index;
// 	int          vary;
// 	Polygon       poly;
// 	gpointer      pr;

// 	bytes = drawable->bpp;


// 	/*  Fill the image with the background color  */
// 	gimp_pixel_rgn_init (&src_rgn, drawable,
// 			     x1, y1, (x2 - x1), (y2 - y1),
// 			     TRUE, TRUE);
// 	for (pr = gimp_pixel_rgns_register (1, &src_rgn);
// 	     pr != NULL;
// 	     pr = gimp_pixel_rgns_process (pr))
// 	{
// 		size = src_rgn.w * src_rgn.h;
// 		dest = src_rgn.data;

// 		for (i = 0; i < src_rgn.h ; i++)
// 		{
// 			d = dest;
// 			for (j = 0; j < src_rgn.w ; j++)
// 			{
// 				for (k = 0; k < bytes; k++)
// 					d[k] = back[k];
// 				d += bytes;
// 			}
// 			dest += src_rgn.rowstride;
// 		}
// 	}
// 	dest = NULL;


// 	size = (grid_rows + grid_row_pad) * (grid_cols + grid_col_pad);
// 	frac_size = size * mvals.color_variation;
// 	count = 0;

// 	for (i = -grid_row_pad; i < grid_rows; i++)
// 		for (j = -grid_col_pad; j < grid_cols; j++)
// 		{
// 			vary = ((random_int_range (0, size)) < frac_size) ? 1 : 0;

// 			index = i * grid_rowstride + j * grid_multiple;

// 			switch (mvals.tile_type)
// 			{
// 			case SQUARES:
// 				polygon_reset (&poly);
// 				polygon_add_point (&poly,
// 						   grid[index].x,
// 						   grid[index].y);
// 				polygon_add_point (&poly,
// 						   grid[index + 1].x,
// 						   grid[index + 1].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_rowstride + 1].x,
// 						   grid[index + grid_rowstride + 1].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_rowstride].x,
// 						   grid[index + grid_rowstride].y);

// 				process_poly (&poly, mvals.tile_allow_split, drawable, col, vary,
// 					      x1, y1, x2, y2, dest);
// 				break;

// 			case HEXAGONS:
// 				/*  The main hexagon  */
// 				polygon_reset (&poly);
// 				polygon_add_point (&poly,
// 						   grid[index].x,
// 						   grid[index].y);
// 				polygon_add_point (&poly,
// 						   grid[index + 1].x,
// 						   grid[index + 1].y);
// 				polygon_add_point (&poly,
// 						   grid[index + 2].x,
// 						   grid[index + 2].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_rowstride + 1].x,
// 						   grid[index + grid_rowstride + 1].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_rowstride].x,
// 						   grid[index + grid_rowstride].y);
// 				polygon_add_point (&poly,
// 						   grid[index + 3].x,
// 						   grid[index + 3].y);
// 				process_poly (&poly, mvals.tile_allow_split, drawable, col, vary,
// 					      x1, y1, x2, y2, dest);

// 				/*  The auxillary hexagon  */
// 				polygon_reset (&poly);
// 				polygon_add_point (&poly,
// 						   grid[index + 2].x,
// 						   grid[index + 2].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_multiple * 2 - 1].x,
// 						   grid[index + grid_multiple * 2 - 1].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_rowstride + grid_multiple].x,
// 						   grid[index + grid_rowstride + grid_multiple].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_rowstride + grid_multiple + 3].x,
// 						   grid[index + grid_rowstride + grid_multiple + 3].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_rowstride + 2].x,
// 						   grid[index + grid_rowstride + 2].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_rowstride + 1].x,
// 						   grid[index + grid_rowstride + 1].y);
// 				process_poly (&poly, mvals.tile_allow_split, drawable, col, vary,
// 					      x1, y1, x2, y2, dest);
// 				break;

// 			case OCTAGONS:
// 				/*  The main octagon  */
// 				polygon_reset (&poly);
// 				for (k = 0; k < 8; k++)
// 					polygon_add_point (&poly,
// 							   grid[index + k].x,
// 							   grid[index + k].y);
// 				process_poly (&poly, mvals.tile_allow_split, drawable, col, vary,
// 					      x1, y1, x2, y2, dest);

// 				/*  The auxillary octagon  */
// 				polygon_reset (&poly);
// 				polygon_add_point (&poly,
// 						   grid[index + 3].x,
// 						   grid[index + 3].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_multiple * 2 - 2].x,
// 						   grid[index + grid_multiple * 2 - 2].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_multiple * 2 - 3].x,
// 						   grid[index + grid_multiple * 2 - 3].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_rowstride + grid_multiple].x,
// 						   grid[index + grid_rowstride + grid_multiple].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_rowstride + grid_multiple * 2 - 1].x,
// 						   grid[index + grid_rowstride + grid_multiple * 2 - 1].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_rowstride + 2].x,
// 						   grid[index + grid_rowstride + 2].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_rowstride + 1].x,
// 						   grid[index + grid_rowstride + 1].y);
// 				polygon_add_point (&poly,
// 						   grid[index + 4].x,
// 						   grid[index + 4].y);
// 				process_poly (&poly, mvals.tile_allow_split, drawable, col, vary,
// 					      x1, y1, x2, y2, dest);

// 				/*  The main square  */
// 				polygon_reset (&poly);
// 				polygon_add_point (&poly,
// 						   grid[index + 2].x,
// 						   grid[index + 2].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_multiple * 2 - 1].x,
// 						   grid[index + grid_multiple * 2 - 1].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_multiple * 2 - 2].x,
// 						   grid[index + grid_multiple * 2 - 2].y);
// 				polygon_add_point (&poly,
// 						   grid[index + 3].x,
// 						   grid[index + 3].y);
// 				process_poly (&poly, FALSE, drawable, col, vary,
// 					      x1, y1, x2, y2, dest);

// 				/*  The auxillary square  */
// 				polygon_reset (&poly);
// 				polygon_add_point (&poly,
// 						   grid[index + 5].x,
// 						   grid[index + 5].y);
// 				polygon_add_point (&poly,
// 						   grid[index + 4].x,
// 						   grid[index + 4].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_rowstride + 1].x,
// 						   grid[index + grid_rowstride + 1].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_rowstride].x,
// 						   grid[index + grid_rowstride].y);
// 				process_poly (&poly, FALSE, drawable, col, vary,
// 					      x1, y1, x2, y2, dest);
// 				break;
// 			case TRIANGLES:
// 				/*  Lower left  */
// 				polygon_reset (&poly);
// 				polygon_add_point (&poly,
// 						   grid[index].x,
// 						   grid[index].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_multiple].x,
// 						   grid[index + grid_multiple].y);
// 				polygon_add_point (&poly,
// 						   grid[index + 1].x,
// 						   grid[index + 1].y);
// 				process_poly (&poly, mvals.tile_allow_split, drawable, col, vary,
// 					      x1, y1, x2, y2, dest);

// 				/*  lower right  */
// 				polygon_reset (&poly);
// 				polygon_add_point (&poly,
// 						   grid[index + 1].x,
// 						   grid[index + 1].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_multiple].x,
// 						   grid[index + grid_multiple].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_multiple + 1].x,
// 						   grid[index + grid_multiple + 1].y);
// 				process_poly (&poly, mvals.tile_allow_split, drawable, col, vary,
// 					      x1, y1, x2, y2, dest);

// 				/*  upper left  */
// 				polygon_reset (&poly);
// 				polygon_add_point (&poly,
// 						   grid[index + 1].x,
// 						   grid[index + 1].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_multiple + grid_rowstride].x,
// 						   grid[index + grid_multiple + grid_rowstride].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_rowstride].x,
// 						   grid[index + grid_rowstride].y);
// 				process_poly (&poly, mvals.tile_allow_split, drawable, col, vary,
// 					      x1, y1, x2, y2, dest);

// 				/*  upper right  */
// 				polygon_reset (&poly);
// 				polygon_add_point (&poly,
// 						   grid[index + 1].x,
// 						   grid[index + 1].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_multiple +1 ].x,
// 						   grid[index + grid_multiple +1 ].y);
// 				polygon_add_point (&poly,
// 						   grid[index + grid_multiple + grid_rowstride].x,
// 						   grid[index + grid_multiple + grid_rowstride].y);
// 				process_poly (&poly, mvals.tile_allow_split, drawable, col, vary,
// 					      x1, y1, x2, y2, dest);
// 				break;

// 			}
// 		}

// }

// void MosaicProcesser::polygon_add_point (Polygon *poly,
// 					 double  x,
// 					 double  y)
// {
// 	if (poly->npts < 12) {
// 		poly->pts[poly->npts].x = x;
// 		poly->pts[poly->npts].y = y;
// 		poly->npts++;
// 	}
// }

// void MosaicProcesser::polygon_reset (Polygon *poly)
// {
// 	poly->npts = 0;
// }

// void MosaicProcesser::process_poly (Polygon      *poly,
// 				    bool      allow_split,
// 				    GimpDrawable *drawable,
// 				    uchar       *col,
// 				    bool      vary,
// 				    int          x1,
// 				    int          y1,
// 				    int          x2,
// 				    int          y2,
// 				    uchar       *dest)
// {
// 	double dir[2];
// 	double loc[2];
// 	double cx = 0.0, cy = 0.0;
// 	double magnitude;
// 	double distance;
// 	double color_vary;

// 	/*  determine the variation of tile color based on tile number  */
// 	color_vary = vary ? fp_rand (mvals.color_variation) : 0;
// 	color_vary = (g_random_int_range (0, 2)) ? color_vary * 127 : -color_vary * 127;

// 	/*  Determine direction of edges inside polygon, if any  */
// 	find_poly_dir (poly, m_grad, h_grad, v_grad, dir, loc, x1, y1, x2, y2);
// 	magnitude = sqrt ((dir[0] - 128) * (dir[0] - 128)
// 			  + (dir[1] - 128) * (dir[1] - 128));

// 	/*  Find the center of the polygon  */
// 	polygon_find_center (poly, &cx, &cy);
// 	distance = sqrt ((loc[0] - cx) * (loc[0] - cx)
// 			 + (loc[1] - cy) * (loc[1] - cy));

// 	/*  If the magnitude of direction inside the polygon is greater than
// 	 *  THRESHOLD, split the polygon into two new polygons
// 	 */
// 	if (magnitude > MAG_THRESHOLD &&
// 	    (2 * distance / mvals.tile_size) < 0.5 && allow_split)
// 	{
// 		split_poly (poly, drawable, col, dir, color_vary, x1, y1, x2, y2, dest);
// 	}
// 	else
// 	{
// 		/*  Otherwise, render the original polygon  */
// 		render_poly (poly, drawable, col, color_vary, x1, y1, x2, y2, dest);
// 	}
// }

// void MosaicProcesser::render_poly (Polygon *poly,
// 				   GimpDrawable *drawable,
// 				   uchar       *col,
// 				   double       vary,
// 				   int          x1,
// 				   int          y1,
// 				   int          x2,
// 				   int          y2,
// 				   uchar       *dest)
// {
// 	double cx = 0.0;
// 	double cy = 0.0;

// 	polygon_find_center (poly, &cx, &cy);

// 	if (mvals.color_averaging)
// 		find_poly_color (poly, drawable, col, vary, x1, y1, x2, y2);

// 	scale_poly (poly, cx, cy, scale);

// 	if (mvals.color_averaging)
// 		fill_poly_color (poly, drawable, col, x1, y1, x2, y2, dest);
// 	else
// 		fill_poly_image (poly, drawable, vary, x1, y1, x2, y2, dest);
// }


// void MosaicProcesser::split_poly (Polygon      *poly,
// 				  GimpDrawable *drawable,
// 				  uchar       *col,
// 				  double      *dir,
// 				  double       vary,
// 				  int          x1,
// 				  int          y1,
// 				  int          x2,
// 				  int          y2,
// 				  uchar       *dest)
// {
// 	Polygon new_poly;
// 	double spacing;
// 	double cx = 0.0;
// 	double cy = 0.0;
// 	double magnitude;
// 	double vec[2];
// 	double pt[2];

// 	spacing = mvals.tile_spacing / (2.0 * scale);

// 	polygon_find_center (poly, &cx, &cy);
// 	polygon_translate (poly, -cx, -cy);

// 	magnitude = sqrt (SQR (dir[0] - 128) + SQR (dir[1] - 128));
// 	vec[0] = -(dir[1] - 128) / magnitude;
// 	vec[1] = (dir[0] - 128) / magnitude;
// 	pt[0] = -vec[1] * spacing;
// 	pt[1] = vec[0] * spacing;

// 	polygon_reset (&new_poly);
// 	clip_poly (vec, pt, poly, &new_poly);
// 	polygon_translate (&new_poly, cx, cy);

// 	if (new_poly.npts)
// 	{
// 		if (mvals.color_averaging)
// 			find_poly_color (&new_poly, drawable, col, vary, x1, y1, x2, y2);
// 		scale_poly (&new_poly, cx, cy, scale);
// 		if (mvals.color_averaging)
// 			fill_poly_color (&new_poly, drawable, col, x1, y1, x2, y2, dest);
// 		else
// 			fill_poly_image (&new_poly, drawable, vary, x1, y1, x2, y2, dest);
// 	}

// 	vec[0] = -vec[0];
// 	vec[1] = -vec[1];
// 	pt[0] = -pt[0];
// 	pt[1] = -pt[1];

// 	polygon_reset (&new_poly);
// 	clip_poly (vec, pt, poly, &new_poly);
// 	polygon_translate (&new_poly, cx, cy);

// 	if (new_poly.npts)
// 	{
// 		if (mvals.color_averaging)
// 			find_poly_color (&new_poly, drawable, col, vary, x1, y1, x2, y2);

// 		scale_poly (&new_poly, cx, cy, scale);

// 		if (mvals.color_averaging)
// 			fill_poly_color (&new_poly, drawable, col, x1, y1, x2, y2, dest);
// 		else
// 			fill_poly_image (&new_poly, drawable, vary, x1, y1, x2, y2, dest);
// 	}
// }

// bool MosaicProcesser::polygon_find_center (Polygon *poly,
// 					       double *cx,
// 					       double *cy)
// {
// 	uint i;

// 	if (!poly->npts)
// 		return FALSE;

// 	*cx = 0.0;
// 	*cy = 0.0;

// 	for (i = 0; i < poly->npts; i++)
// 	{
// 		*cx += poly->pts[i].x;
// 		*cy += poly->pts[i].y;
// 	}

// 	*cx /= poly->npts;
// 	*cy /= poly->npts;

// 	return TRUE;
// }

// bool MosaicProcesser::polygon_extents (Polygon *poly,
// 					   double *min_x,
// 					   double *min_y,
// 					   double *max_x,
// 					   double *max_y)
// {
// 	uint i;

// 	if (!poly->npts)
// 		return FALSE;

// 	*min_x = *max_x = poly->pts[0].x;
// 	*min_y = *max_y = poly->pts[0].y;

// 	for (i = 1; i < poly->npts; i++)
// 	{
// 		*min_x = qMin(*min_x, poly->pts[i].x);
// 		*max_x = qMax (*max_x, poly->pts[i].x);
// 		*min_y = qMin(*min_y, poly->pts[i].y);
// 		*max_y = qMax (*max_y, poly->pts[i].y);
// 	}

// 	return TRUE;
// }

// void MosaicProcesser::polygon_scale (Polygon *poly,
// 				     double  poly_scale)
// {
// 	uint i;

// 	for (i = 0; i < poly->npts; i++)
// 	{
// 		poly->pts[i].x *= poly_scale;
// 		poly->pts[i].y *= poly_scale;
// 	}
// }

// void MosaicProcesser::polygon_translate (Polygon *poly,
// 					 double  tx,
// 					 double  ty)
// {
// 	uint i;

// 	for (i = 0; i < poly->npts; i++)
// 	{
// 		poly->pts[i].x += tx;
// 		poly->pts[i].y += ty;
// 	}
// }

// void MosaicProcesser::convert_segment (int  x1,
// 				       int  y1,
// 				       int  x2,
// 				       int  y2,
// 				       int  offset,
// 				       int *min,
// 				       int *max)
// {
// 	int    ydiff, y, tmp;
// 	double xinc, xstart;

// 	if (y1 > y2)
// 	{
// 		tmp = y2; y2 = y1; y1 = tmp;
// 		tmp = x2; x2 = x1; x1 = tmp;
// 	}

// 	ydiff = y2 - y1;

// 	if (ydiff)
// 	{
// 		xinc = (double) (x2 - x1) / (double) ydiff;
// 		xstart = x1 + 0.5 * xinc;

// 		for (y = y1; y < y2; y++)
// 		{
// 			min[y - offset] = qMin(min[y - offset], xstart);
// 			max[y - offset] = qMax(max[y - offset], xstart);

// 			xstart += xinc;
// 		}
// 	}
// }

// double MosaicProcesser::calc_spec_contrib (SpecVec *vecs,
// 					   int     n,
// 					   double  x,
// 					   double  y)
// {
// 	int i;
// 	double contrib = 0;

// 	for (i = 0; i < n; i++)
// 	{
// 		double x_p, y_p;
// 		double dist;

// 		x_p = x - vecs[i].base_x;
// 		y_p = y - vecs[i].base_y;

// 		dist = fabs (x_p * vecs[i].norm_x + y_p * vecs[i].norm_y);

// 		if (mvals.tile_surface == ROUGH)
// 		{
// 			/*  If the surface is rough, randomly perturb the distance  */
// 			dist -= dist * g_random_double ();
// 		}

// 		/*  If the distance to an edge is less than the tile_spacing, there
// 		 *  will be no highlight as the tile blends to background here
// 		 */
// 		if (dist < 1.0)
// 			contrib += vecs[i].light;
// 		else if (dist <= mvals.tile_height)
// 			contrib += vecs[i].light * (1.0 - (dist / mvals.tile_height));
// 	}

// 	return contrib / 4.0;
// }

// void MosaicProcesser::calc_spec_vec(SpecVec *vec,
// 				    int     x1,
// 				    int     y1,
// 				    int     x2,
// 				    int     y2)
// {
// 	double r;
	
// 	vec->base_x = x1;
// 	vec->base_y = y1;

// 	r = sqrt ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

// 	if (r > 0.0)
// 	{
// 		vec->norm_x = -(y2 - y1) / r;
// 		vec->norm_y =  (x2 - x1) / r;
// 	}
// 	else
// 	{
// 		vec->norm_x = 0;
// 		vec->norm_y = 0;
// 	}

// 	vec->light = vec->norm_x * light_x + vec->norm_y * light_y;
// }


// void MosaicProcesser::fill_poly_color (Polygon      *poly,
// 				       QImage *image,
// 				       uchar       *col,
// 				       int          x1,
// 				       int          y1,
// 				       int          x2,
// 				       int          y2,
// 				       uchar       *dest)
// {
// 	QImage src_rgn;
// 	double       dmin_x = 0.0, dmin_y = 0.0;
// 	double       dmax_x = 0.0, dmax_y = 0.0;
// 	int          xs, ys;
// 	int          xe, ye;
// 	int          min_x, min_y;
// 	int          max_x, max_y;
// 	int          size_x, size_y;
// 	int         *max_scanlines, *max_scanlines_iter;
// 	int         *min_scanlines, *min_scanlines_iter;
// 	int         *vals;
// 	int          val;
// 	int          pixel;
// 	int          bytes;
// 	uchar        buf[4];
// 	int          b, i, j, k, x, y;
// 	double       contrib;
// 	double       xx, yy;
// 	int          supersample;
// 	int          supersample2;
// 	Vertex       *pts_tmp;
// 	const int    poly_npts = poly->npts;

// 	/*  Determine antialiasing  */
// 	if (mvals.antialiasing)
// 	{
// 		supersample = SUPERSAMPLE;
// 		supersample2 = SQR (supersample);
// 	}
// 	else
// 	{
// 		supersample = supersample2 = 1;
// 	}

// 	bytes = bytes_num(image);

// 	if (poly_npts)
// 	{
// 		pts_tmp = poly->pts;
// 		xs = (int) pts_tmp[poly_npts - 1].x;
// 		ys = (int) pts_tmp[poly_npts - 1].y;
// 		xe = (int) pts_tmp->x;
// 		ye = (int) pts_tmp->y;

// 		calc_spec_vec (vecs, xs, ys, xe, ye);

// 		for (i = 1; i < poly_npts; i++)
// 		{
// 			xs = (int) (pts_tmp->x);
// 			ys = (int) (pts_tmp->y);
// 			pts_tmp++;
// 			xe = (int) pts_tmp->x;
// 			ye = (int) pts_tmp->y;

// 			calc_spec_vec (vecs+i, xs, ys, xe, ye);
// 		}
// 	}

// 	polygon_extents (poly, &dmin_x, &dmin_y, &dmax_x, &dmax_y);

// 	min_x = (int) dmin_x;
// 	min_y = (int) dmin_y;
// 	max_x = (int) dmax_x;
// 	max_y = (int) dmax_y;

// 	size_y = (max_y - min_y) * supersample;
// 	size_x = (max_x - min_x) * supersample;

// 	min_scanlines = min_scanlines_iter = new int[size_y];
// 	max_scanlines = max_scanlines_iter = new int[size_y];

// 	for (i = 0; i < size_y; i++)
// 	{
// 		min_scanlines[i] = max_x * supersample;
// 		max_scanlines[i] = min_x * supersample;
// 	}

// 	if(poly_npts)
// 	{
// 		pts_tmp = poly->pts;
// 		xs = (int) pts_tmp[poly_npts-1].x;
// 		ys = (int) pts_tmp[poly_npts-1].y;
// 		xe = (int) pts_tmp->x;
// 		ye = (int) pts_tmp->y;

// 		xs *= supersample;
// 		ys *= supersample;
// 		xe *= supersample;
// 		ye *= supersample;

// 		convert_segment (xs, ys, xe, ye, min_y * supersample,
// 				 min_scanlines, max_scanlines);

// 		for (i = 1; i < poly_npts; i++)
// 		{
// 			xs = (int) pts_tmp->x;
// 			ys = (int) pts_tmp->y;
// 			pts_tmp++;
// 			xe = (int) pts_tmp->x;
// 			ye = (int) pts_tmp->y;

// 			xs *= supersample;
// 			ys *= supersample;
// 			xe *= supersample;
// 			ye *= supersample;

// 			convert_segment (xs, ys, xe, ye, min_y * supersample,
// 					 min_scanlines, max_scanlines);
// 		}
// 	}

// 	src_rgn = drawable;

// 	vals = new int[size_x];
// 	for (i = 0; i < size_y; i++, min_scanlines_iter++, max_scanlines_iter++)
// 	{
// 		if (! (i % supersample))
// 			memset (vals, 0, sizeof (int) * size_x);

// 		yy = (double) i / (double) supersample + min_y;

// 		for (j = *min_scanlines_iter; j < *max_scanlines_iter; j++)
// 		{
// 			x = j - min_x * supersample;
// 			vals[x] += 255;
// 		}

// 		if (! ((i + 1) % supersample))
// 		{
// 			y = (i / supersample) + min_y;

// 			if (y >= y1 && y < y2)
// 			{
// 				for (j = 0; j < size_x; j += supersample)
// 				{
// 					x = (j / supersample) + min_x;

// 					if (x >= x1 && x < x2)
// 					{
// 						val = 0;

// 						for (k = 0; k < supersample; k++)
// 							val += vals[j + k];

// 						val /= supersample2;

// 						if (val > 0)
// 						{

// 							xx = (double) j / (double) supersample + min_x;
// 							contrib = calc_spec_contrib (vecs, poly_npts, xx, yy);

// 							for (b = 0; b < bytes; b++)
// 							{
// 								pixel = col[b] + (int) (((contrib < 0.0)?(col[b] - back[b]):(fore[b] - col[b])) * contrib);

// 								buf[b] = ((pixel * val) + (back[b] * (255 - val))) / 255;
// 							}

// 							if (dest)
// 								memcpy (dest + ((y - y1) * (x2 - x1) + (x - x1)) * bytes, buf, bytes);
// 							else
// 								gimp_pixel_rgn_set_pixel (&src_rgn, buf, x, y);
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}

// 	delete vals;
// 	delete min_scanlines;
// 	delete max_scanlines;
// }

// void MosaicProcesser::fill_poly_image (Polygon      *poly,
// 				       QImage *image,
// 				       double       vary,
// 				       int          x1,
// 				       int          y1,
// 				       int          x2,
// 				       int          y2,
// 				       uchar       *dest)
// {
// 	QImage  src_rgn, dest_rgn;
// 	double       dmin_x = 0.0, dmin_y = 0.0;
// 	double       dmax_x = 0.0, dmax_y = 0.0;
// 	int          xs, ys;
// 	int          xe, ye;
// 	int          min_x, min_y;
// 	int          max_x, max_y;
// 	int          size_x, size_y;
// 	int         *max_scanlines;
// 	int         *min_scanlines;
// 	int         *vals;
// 	int          val;
// 	int          pixel;
// 	int          bytes;
// 	uchar        buf[4];
// 	int          b, i, j, k, x, y;
// 	double       contrib;
// 	double       xx, yy;
// 	int          supersample;
// 	int          supersample2;

// 	/*  Determine antialiasing  */
// 	if (mvals.antialiasing)
// 	{
// 		supersample = SUPERSAMPLE;
// 		supersample2 = supersample * supersample;
// 	}
// 	else
// 	{
// 		supersample = supersample2 = 1;
// 	}

// 	bytes = bytes_num(*image);
// 	for (i = 0; i < poly->npts; i++)
// 	{
// 		xs = (int) ((i) ? poly->pts[i-1].x : poly->pts[poly->npts-1].x);
// 		ys = (int) ((i) ? poly->pts[i-1].y : poly->pts[poly->npts-1].y);
// 		xe = (int) poly->pts[i].x;
// 		ye = (int) poly->pts[i].y;

// 		calc_spec_vec (vecs+i, xs, ys, xe, ye);
// 	}

// 	polygon_extents (poly, &dmin_x, &dmin_y, &dmax_x, &dmax_y);

// 	min_x = (int) dmin_x;
// 	min_y = (int) dmin_y;
// 	max_x = (int) dmax_x;
// 	max_y = (int) dmax_y;

// 	size_y = (max_y - min_y) * supersample;
// 	size_x = (max_x - min_x) * supersample;

// 	min_scanlines = new int[size_y];
// 	max_scanlines = new int[size_y];

// 	for (i = 0; i < size_y; i++)
// 	{
// 		min_scanlines[i] = max_x * supersample;
// 		max_scanlines[i] = min_x * supersample;
// 	}

// 	for (i = 0; i < poly->npts; i++)
// 	{
// 		xs = (int) ((i) ? poly->pts[i-1].x : poly->pts[poly->npts-1].x);
// 		ys = (int) ((i) ? poly->pts[i-1].y : poly->pts[poly->npts-1].y);
// 		xe = (int) poly->pts[i].x;
// 		ye = (int) poly->pts[i].y;

// 		xs *= supersample;
// 		ys *= supersample;
// 		xe *= supersample;
// 		ye *= supersample;

// 		convert_segment (xs, ys, xe, ye, min_y * supersample,
// 				 min_scanlines, max_scanlines);
// 	}

// 	src_rgn = image;
// 	if (!dest)
// 		dest_rgn = image;

// 	vals = new int[size_x];
// 	for (i = 0; i < size_y; i++)
// 	{
// 		if (! (i % supersample))
// 			memset (vals, 0, sizeof (int) * size_x);

// 		yy = (double) i / (double) supersample + min_y;

// 		for (j = min_scanlines[i]; j < max_scanlines[i]; j++)
// 		{
// 			x = j - min_x * supersample;
// 			vals[x] += 255;
// 		}

// 		if (! ((i + 1) % supersample))
// 		{
// 			y = (i / supersample) + min_y;

// 			if (y >= y1 && y < y2)
// 			{
// 				for (j = 0; j < size_x; j += supersample)
// 				{
// 					x = (j / supersample) + min_x;

// 					if (x >= x1 && x < x2)
// 					{
// 						val = 0;
// 						for (k = 0; k < supersample; k++)
// 							val += vals[j + k];
// 						val /= supersample2;

// 						if (val > 0)
// 						{
// 							xx = (double) j / (double) supersample + min_x;
// 							contrib = calc_spec_contrib (vecs, poly->npts, xx, yy);

// 							ImageUtility::getPixel(src_rgn, buf, x, y);

// 							for (b = 0; b < bytes; b++)
// 							{
// 								if (contrib < 0.0)
// 									pixel = buf[b] + (int) ((buf[b] - back[b]) * contrib);
// 								else
// 									pixel = buf[b] + (int) ((fore[b] - buf[b]) * contrib);

// 								/*  factor in per-tile intensity variation  */
// 								pixel += vary;
// 								pixel = CLAMP (pixel, 0, 255);

// 								buf[b] = ((back[b] << 8) + (pixel - back[b]) * val) >> 8;
// 							}

// 							if (dest)
// 								memcpy (dest + ((y - y1) * (x2 - x1) + (x - x1)) * bytes, buf, bytes);
// 							else
// 								ImageUtility::setPixel(dest_rgn, buf, x, y);
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}

// 	delete vals;
// 	delete min_scanlines;
// 	delete max_scanlines;
// }


// static void MosaicProcesser::find_poly_color (Polygon      *poly,
// 					      QImage *image,
// 					      uchar       *col,
// 					      double       color_var,
// 					      int          x1,
// 					      int          y1,
// 					      int          x2,
// 					      int          y2)
// {
// 	QImage  src_rgn;
// 	double       dmin_x = 0.0, dmin_y = 0.0;
// 	double       dmax_x = 0.0, dmax_y = 0.0;
// 	int          xs, ys;
// 	int          xe, ye;
// 	int          min_x, min_y;
// 	int          max_x, max_y;
// 	int          size_x, size_y;
// 	int         *max_scanlines;
// 	int         *min_scanlines;
// 	int          col_sum[4] = {0, 0, 0, 0};
// 	int          bytes;
// 	int          b, count;
// 	int          i, j, y;

// 	count = 0;

// 	bytes = bytes_num(*image);

// 	polygon_extents (poly, &dmin_x, &dmin_y, &dmax_x, &dmax_y);

// 	min_x = (int) dmin_x;
// 	min_y = (int) dmin_y;
// 	max_x = (int) dmax_x;
// 	max_y = (int) dmax_y;

// 	size_y = max_y - min_y;
// 	size_x = max_x - min_x;

// 	min_scanlines = new int[size_y];
// 	max_scanlines = new int[size_y];

// 	for (i = 0; i < size_y; i++)
// 	{
// 		min_scanlines[i] = max_x;
// 		max_scanlines[i] = min_x;
// 	}

// 	for (i = 0; i < poly->npts; i++)
// 	{
// 		xs = (int) ((i) ? poly->pts[i-1].x : poly->pts[poly->npts-1].x);
// 		ys = (int) ((i) ? poly->pts[i-1].y : poly->pts[poly->npts-1].y);
// 		xe = (int) poly->pts[i].x;
// 		ye = (int) poly->pts[i].y;

// 		convert_segment (xs, ys, xe, ye, min_y,
// 				 min_scanlines, max_scanlines);
// 	}

// 	src_rgn = *image;

// 	for (i = 0; i < size_y; i++)
// 	{
// 		y = i + min_y;

// 		if (y >= y1 && y < y2)
// 		{
// 			for (j = min_scanlines[i]; j < max_scanlines[i]; j++)
// 			{
// 				if (j >= x1 && j < x2)
// 				{
// 					/* this adaption may not be correct */
// 					ImageUtility::getPixel(src_rgn, col, j, y);

// 					for (b = 0; b < bytes; b++)
// 						col_sum[b] += col[b];

// 					count++;
// 				}
// 			}
// 		}
// 	}

// 	if (count)
// 		for (b = 0; b < bytes; b++)
// 		{
// 			col_sum[b] = (int) (col_sum[b] / count + color_var);
// 			col[b] = CLAMP0255 (col_sum[b]);
// 		}

// 	delete min_scanlines;
// 	delete max_scanlines;
// }


// void MosaicProcesser::find_poly_dir (Polygon *poly, uchar  *m_gr,
// 				     uchar  *h_gr, uchar  *v_gr,
// 				     double *dir, double *loc,
// 				     int x1, int y1,
// 				     int x2, int y2)
// {
// 	double dmin_x = 0.0, dmin_y = 0.0;
// 	double dmax_x = 0.0, dmax_y = 0.0;
// 	int    xs, ys;
// 	int    xe, ye;
// 	int    min_x, min_y;
// 	int    max_x, max_y;
// 	int    size_x, size_y;
// 	int   *max_scanlines;
// 	int   *min_scanlines;
// 	uchar *dm, *dv, *dh;
// 	int    count, total;
// 	int    rowstride;
// 	int    i, j;

// 	rowstride = (x2 - x1);
// 	count = 0;
// 	total = 0;
// 	dir[0] = 0.0;
// 	dir[1] = 0.0;
// 	loc[0] = 0.0;
// 	loc[1] = 0.0;

// 	polygon_extents(poly, &dmin_x, &dmin_y, &dmax_x, &dmax_y);

// 	min_x = (int) dmin_x;
// 	min_y = (int) dmin_y;
// 	max_x = (int) dmax_x;
// 	max_y = (int) dmax_y;

// 	size_y = max_y - min_y;
// 	size_x = max_x - min_x;

// 	min_scanlines = new int[size_y];
// 	max_scanlines = new int[size_y];

// 	for (i = 0; i < size_y; i++)
// 	{
// 		min_scanlines[i] = max_x;
// 		max_scanlines[i] = min_x;
// 	}

// 	for (i = 0; i < poly->npts; i++)
// 	{
// 		xs = (int) ((i) ? poly->pts[i-1].x : poly->pts[poly->npts-1].x);
// 		ys = (int) ((i) ? poly->pts[i-1].y : poly->pts[poly->npts-1].y);
// 		xe = (int) poly->pts[i].x;
// 		ye = (int) poly->pts[i].y;

// 		convert_segment (xs, ys, xe, ye, min_y,
// 				 min_scanlines, max_scanlines);
// 	}

// 	for (i = 0; i < size_y; i++)
// 	{
// 		if ((i + min_y) >= y1 && (i + min_y) < y2)
// 		{
// 			dm = m_gr + (i + min_y - y1) * rowstride - x1;
// 			dh = h_gr + (i + min_y - y1) * rowstride - x1;
// 			dv = v_gr + (i + min_y - y1) * rowstride - x1;

// 			for (j = min_scanlines[i]; j < max_scanlines[i]; j++)
// 			{
// 				if (j >= x1 && j < x2)
// 				{
// 					if (dm[j] > MAG_THRESHOLD)
// 					{
// 						dir[0] += dh[j];
// 						dir[1] += dv[j];
// 						loc[0] += j;
// 						loc[1] += i + min_y;
// 						count++;
// 					}
// 					total++;
// 				}
// 			}
// 		}
// 	}

// 	if (!total)
// 		return;

// 	if ((double) count / (double) total > COUNT_THRESHOLD)
// 	{
// 		dir[0] /= count;
// 		dir[1] /= count;
// 		loc[0] /= count;
// 		loc[1] /= count;
// 	}
// 	else
// 	{
// 		dir[0] = 128.0;
// 		dir[1] = 128.0;
// 		loc[0] = 0.0;
// 		loc[1] = 0.0;
// 	}

// 	delete min_scanlines;
// 	delete max_scanlines;
// }


// void MosaicProcesser::clip_point (double *dir,
// 				  double *pt,
// 				  double  x1,
// 				  double  y1,
// 				  double  x2,
// 				  double  y2,
// 				  Polygon *poly_new)
// {
// 	double det, m11, m12, m21, m22;
// 	double side1, side2;
// 	double t;
// 	double vec[2];

// 	x1 -= pt[0]; x2 -= pt[0];
// 	y1 -= pt[1]; y2 -= pt[1];

// 	side1 = x1 * -dir[1] + y1 * dir[0];
// 	side2 = x2 * -dir[1] + y2 * dir[0];

// 	/*  If both points are to be clipped, ignore  */
// 	if (side1 < 0.0 && side2 < 0.0)
// 	{
// 		return;
// 	}
// 	/*  If both points are non-clipped, set point  */
// 	else if (side1 >= 0.0 && side2 >= 0.0)
// 	{
// 		polygon_add_point (poly_new, x2 + pt[0], y2 + pt[1]);
// 		return;
// 	}
// 	/*  Otherwise, there is an intersection...  */
// 	else
// 	{
// 		vec[0] = x1 - x2;
// 		vec[1] = y1 - y2;
// 		det = dir[0] * vec[1] - dir[1] * vec[0];

// 		if (det == 0.0)
// 		{
// 			polygon_add_point (poly_new, x2 + pt[0], y2 + pt[1]);
// 			return;
// 		}

// 		m11 = vec[1] / det;
// 		m12 = -vec[0] / det;
// 		m21 = -dir[1] / det;
// 		m22 = dir[0] / det;

// 		t = m11 * x1 + m12 * y1;

// 		/*  If the first point is clipped, set intersection and point  */
// 		if (side1 < 0.0 && side2 > 0.0)
// 		{
// 			polygon_add_point (poly_new, dir[0] * t + pt[0], 
// 					   dir[1] * t + pt[1]);
// 			polygon_add_point (poly_new, x2 + pt[0], y2 + pt[1]);
// 		}
// 		else
// 		{
// 			polygon_add_point (poly_new, dir[0] * t + 
// 					   pt[0], dir[1] * t + pt[1]);
// 		}
// 	}
// }


// void MosaicProcesser::grid_create_squares (gint x1,
// 					   gint y1,
// 					   gint x2,
// 					   gint y2)
// {
//   gint    rows, cols;
//   gint    width, height;
//   gint    i, j;
//   gint    size = (gint) mvals.tile_size;
//   Vertex *pt;

//   width  = x2 - x1;
//   height = y2 - y1;
//   rows = (height + size - 1) / size;
//   cols = (width + size - 1) / size;

//   grid = new Vertex[(cols + 2) * (rows + 2)];
//   grid += (cols + 2) + 1;

//   for (i = -1; i <= rows; i++)
//     for (j = -1; j <= cols; j++)
//       {
//         pt = grid + (i * (cols + 2) + j);

//         pt->x = x1 + j * size + size / 2;
//         pt->y = y1 + i * size + size / 2;
//       }

//   grid_rows = rows;
//   grid_cols = cols;
//   grid_row_pad = 1;
//   grid_col_pad = 1;
//   grid_multiple = 1;
//   grid_rowstride = cols + 2;
// }

// void MosaicProcesser::grid_create_hexagons (gint x1,
// 					    gint y1,
//                       gint x2,
//                       gint y2)
// {
//   gint     rows, cols;
//   gint     width, height;
//   gint     i, j;
//   gdouble  hex_l1, hex_l2, hex_l3;
//   gdouble  hex_width;
//   gdouble  hex_height;
//   Vertex  *pt;

//   width  = x2 - x1;
//   height = y2 - y1;
//   hex_l1 = mvals.tile_size / 2.0;
//   hex_l2 = hex_l1 * 2.0 / sqrt (3.0);
//   hex_l3 = hex_l1 / sqrt (3.0);
//   hex_width = 6 * hex_l1 / sqrt (3.0);
//   hex_height = mvals.tile_size;
//   rows = ((height + hex_height - 1) / hex_height);
//   cols = ((width + hex_width * 2 - 1) / hex_width);

//   grid = new Vertex[(cols + 2) * 4 * (rows + 2)];
//   grid += (cols + 2) * 4 + 4;

//   for (i = -1; i <= rows; i++)
//     for (j = -1; j <= cols; j++)
//       {
//         pt = grid + (i * (cols + 2) * 4 + j * 4);

//         pt[0].x = x1 + hex_width * j + hex_l3;
//         pt[0].y = y1 + hex_height * i;
//         pt[1].x = pt[0].x + hex_l2;
//         pt[1].y = pt[0].y;
//         pt[2].x = pt[1].x + hex_l3;
//         pt[2].y = pt[1].y + hex_l1;
//         pt[3].x = pt[0].x - hex_l3;
//         pt[3].y = pt[0].y + hex_l1;
//       }

//   grid_rows = rows;
//   grid_cols = cols;
//   grid_row_pad = 1;
//   grid_col_pad = 1;
//   grid_multiple = 4;
//   grid_rowstride = (cols + 2) * 4;
// }


// void MosaicProcesser::grid_create_octagons (gint x1,
//                       gint y1,
//                       gint x2,
//                       gint y2)
// {
//   gint     rows, cols;
//   gint     width, height;
//   gint     i, j;
//   gdouble  ts, side, leg;
//   gdouble  oct_size;
//   Vertex  *pt;

//   width = x2 - x1;
//   height = y2 - y1;

//   ts = mvals.tile_size;
//   side = ts / (sqrt (2.0) + 1.0);
//   leg = side * sqrt (2.0) * 0.5;
//   oct_size = ts + side;

//   rows = ((height + oct_size - 1) / oct_size);
//   cols = ((width + oct_size * 2 - 1) / oct_size);

//   grid = new [Vertex, (cols + 2) * 8 * (rows + 2)];
//   grid += (cols + 2) * 8 + 8;

//   for (i = -1; i < rows + 1; i++)
//     for (j = -1; j < cols + 1; j++)
//       {
//         pt = grid + (i * (cols + 2) * 8 + j * 8);

//         pt[0].x = x1 + oct_size * j;
//         pt[0].y = y1 + oct_size * i;
//         pt[1].x = pt[0].x + side;
//         pt[1].y = pt[0].y;
//         pt[2].x = pt[0].x + leg + side;
//         pt[2].y = pt[0].y + leg;
//         pt[3].x = pt[2].x;
//         pt[3].y = pt[0].y + leg + side;
//         pt[4].x = pt[1].x;
//         pt[4].y = pt[0].y + 2 * leg + side;
//         pt[5].x = pt[0].x;
//         pt[5].y = pt[4].y;
//         pt[6].x = pt[0].x - leg;
//         pt[6].y = pt[3].y;
//         pt[7].x = pt[6].x;
//         pt[7].y = pt[2].y;
//       }

//   grid_rows = rows;
//   grid_cols = cols;
//   grid_row_pad = 1;
//   grid_col_pad = 1;
//   grid_multiple = 8;
//   grid_rowstride = (cols + 2) * 8;
// }


// void MosaicProcesser::grid_create_triangles (gint x1,
// 					     gint y1,
// 					     gint x2,
// 					     gint y2)
// {
//   gint     rows, cols;
//   gint     width, height;
//   gint     i, j;
//   gdouble  tri_mid, tri_height;
//   Vertex  *pt;

//   width  = x2 - x1;
//   height = y2 - y1;
//   tri_mid    = mvals.tile_size / 2.0;              /* cos 60 */
//   tri_height = mvals.tile_size / 2.0 * sqrt (3.0); /* sin 60 */

//   rows = (height + 2 * tri_height - 1) / (2 * tri_height);
//   cols = (width + mvals.tile_size - 1) / mvals.tile_size;

//   grid = g_new (Vertex, (cols + 2) * 2 * (rows + 2));
//   grid += (cols + 2) * 2 + 2;

//   for (i = -1; i <= rows; i++)
//     for (j = -1; j <= cols; j++)
//       {
//         pt = grid + (i * (cols + 2) * 2 + j * 2);

//         pt[0].x = x1 + mvals.tile_size * j;
//         pt[0].y = y1 + (tri_height*2) * i;
//         pt[1].x = pt[0].x + tri_mid;
//         pt[1].y = pt[0].y + tri_height;
//       }

//   grid_rows = rows;
//   grid_cols = cols;
//   grid_row_pad = 1;
//   grid_col_pad = 1;
//   grid_multiple = 2;
//   grid_rowstride = (cols + 2) * 2;
// }

MultiProcesser::MultiProcesser(QVector<ImageProcesser*> processers)
{
	m_processers = processers;
}

MultiProcesser::~MultiProcesser()
{
	for (int i = 0; i != m_processers.size(); ++i)
		delete m_processers[i];
}

QImage MultiProcesser::produceProcessedImage(const QImage &image)
{
	QImage dest = image;
	for (int i = 0; i != m_processers.size(); ++i)
		dest = m_processers[i]->produceProcessedImage(dest);
	return dest;
}

MorphoDistanceProcesser::MorphoDistanceProcesser(int rows, int columns, 
				int centerRow, int centerColumn,
				const QVector<int> &matrix,
				SharedArea area)
{
	AreaIterator *iter = 
		new AreaIterator(rows, columns, centerRow, centerColumn, area);
	AreaRgbMap *map = new ErosionMap(rows, columns, centerRow, centerColumn,
					 matrix);
	m_erosion_processer  = 
		new AreaRgbImageProcesser(iter, map, "Erosion");
	m_area = area;
}

MorphoDistanceProcesser::~MorphoDistanceProcesser()
{
	delete m_erosion_processer;
}

QImage MorphoDistanceProcesser::produceProcessedImage(const QImage &image)
{
	int count = 0;
	int size = image.width() * image.height();
	const uchar *bits = image.constBits();
	const uchar *last = bits + size * 4;
	while (bits < last) {
		if (*bits)
			++count;
		bits += 4;
	}
	int step = 0;

	QImage currentImage = image;
	QImage lastImage;
	int *steps = new int[size];
	for (int i = 0; i != size; ++i) {
		steps[i] = 0;
	}
	while (count) {
		++step;
		lastImage = currentImage;
		currentImage = 
			m_erosion_processer->produceProcessedImage(lastImage);
		const uchar *currentBits = currentImage.constBits();
		const uchar *lastBits = lastImage.constBits();
		for (int i = 0; i < size; ++i) {
			if (*currentBits != *lastBits) {
				steps[i] = step;
				--count;
			}
			currentBits += 4;
			lastBits += 4;
		}
	}

	int units;
	if (step == 0)
		units = 0;
	else
		units = 255 / step;

	QImage distanceImage = image;
	uchar *distanceBits = distanceImage.bits();
	for (int i = 0; i < size; ++i) {
		distanceBits[0] = steps[i] * units;
		distanceBits[1] = steps[i] * units;
		distanceBits[2] = steps[i] * units;
		distanceBits += 4;
	}
	
	delete [] steps;
	return distanceImage;
}

MorphoSkeletonProcesser::MorphoSkeletonProcesser()
{
	m_open_processer = getOpenProcesser();
	m_erosion_processer = getErosionProcesser();
}

MorphoSkeletonProcesser::~MorphoSkeletonProcesser()
{
	delete m_open_processer;
	delete m_erosion_processer;
}

QImage MorphoSkeletonProcesser::produceProcessedImage(const QImage &image)
{
	int count = 0;
	int size = image.width() * image.height();
	const uchar *bits = image.constBits();
	const uchar *last = bits + size * 4;
	while (bits < last) {
		if (*bits)
			++count;
		bits += 4;
	}
	
	uchar *sigma = new uchar[size];
	QImage skeleton = image;
	for (int i = 0; i < size; ++i) {
		sigma[i] = 0;
	}
	QImage openImage = image;
	QImage erosionImage = image;
	
	while (count) {
		openImage =
			m_open_processer->produceProcessedImage(skeleton);

		uchar *skeletonBits = skeleton.bits();
		const uchar *erosionBits = erosionImage.constBits();
		const uchar *openBits = openImage.constBits();
		for (int i = 0; i < size; ++i) {
			if (*erosionBits != *openBits) {
				skeletonBits[0] = MAX_PIXEL_VALUE;
				skeletonBits[1] = MAX_PIXEL_VALUE;
				skeletonBits[2] = MAX_PIXEL_VALUE;
				sigma[i] = MAX_PIXEL_VALUE;
			} else {
				skeletonBits[0] = 0;
				skeletonBits[1] = 0;
				skeletonBits[2] = 0;
			}
			skeletonBits += 4;
			erosionBits += 4;
			openBits += 4;
		}

		erosionImage = 
			m_erosion_processer->produceProcessedImage(erosionImage);
	}

	QImage resultImage = image;
	uchar *skeletonBits = resultImage.bits();
	for (int i = 0; i < size; ++ i) {
		skeletonBits[0] = sigma[i];
		skeletonBits[1] = sigma[i];
		skeletonBits[2] = sigma[i];
		skeletonBits += 4;
	}

	delete [] sigma;
	return resultImage;
}

ImageProcesser *MorphoSkeletonProcesser::getOpenProcesser()
{
	QVector<int> matrix;
	int kernel[9] =  { 0, 255, 0,
			   255, 255, 255,
			   0, 255, 0 };

	for (int i = 0; i != 9; ++i)
		matrix.push_back(kernel[i]);
	QVector<ImageProcesser*> processers;
	AreaIterator *iter = 
		new AreaIterator(3, 3, 2, 2, SharedArea(0));
	AreaRgbMap *map = new ErosionMap(3, 3, 2, 2, matrix);
	processers.push_back(new AreaRgbImageProcesser(iter, map, "Erosion"));

	iter = new AreaIterator(3, 3, 2, 2, SharedArea(0));
	map = new ErosionMap(3, 3, 2, 2, matrix);
	processers.push_back(new AreaRgbImageProcesser(iter, map, "Dilation"));

	return new MultiProcesser(processers);
}
ImageProcesser *MorphoSkeletonProcesser::getErosionProcesser()
{
	QVector<int> matrix;
	int kernel[9] =  { 0, 255, 0,
			   255, 255, 255,
			   0, 255, 0 };

	for (int i = 0; i != 9; ++i)
		matrix.push_back(kernel[i]);
	AreaIterator *iter = 
		new AreaIterator(3, 3, 2, 2, SharedArea(0));
	AreaRgbMap *map = new ErosionMap(3, 3, 2, 2, matrix);
	return new AreaRgbImageProcesser(iter, map, "Erosion");
}
