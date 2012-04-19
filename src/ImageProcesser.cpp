#include "ImageProcesser.h"

#include <QImage>
#include <QPainter>

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
	painter->drawPolygon(m_points);
	delete painter;
	return dest;
}
