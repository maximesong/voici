#ifndef _HISTOGRAM_H_
#define _HISTOGRAM_H_

class QImage;

const int SCALE_DEPTH = 256;

class Histogram {
public:
	Histogram(const QImage &image, double r = 11 / 32.0, double g = 16 / 32.0,
		  double b = 5 / 32.0);
	const int *getRHistogram() { return r_histogram; }
	const int *getGHistogram() { return g_histogram; }
	const int *getBHistogram() { return b_histogram; }
	const int *getGrayHistogram() { return gray_histogram; }
private:
	int r_histogram[SCALE_DEPTH];
	int g_histogram[SCALE_DEPTH];
	int b_histogram[SCALE_DEPTH];
	int gray_histogram[SCALE_DEPTH];
};

#endif /* _HISTOGRAM_H_ */
