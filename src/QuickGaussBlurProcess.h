#ifndef _QUICKGAUSSBLURPROCESS_H_
#define _QUICKGAUSSBLURPROCESS_H_
	
#include <QImage>

#include "ImageProcess.h"

class QuickGaussBlurProcess : public ImageProcess {
public:
	QuickGaussBlurProcess(double horizontal, double vertical,
			      const QString processName = "Quick Gauss");
	virtual QImage generateNewImage(const QImage &image);
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
	
#endif /* _QUICKGAUSSBLURPROCESS_H_ */
