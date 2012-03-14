#ifndef _HISTOGRAM_H_
#define _HISTOGRAM_H_

class QImage;

class Histogram {
public:
	Histogram(const QImage &image, double r = 11 / 32, double g = 16 / 32,
		  double b = 5 / 32);
	const int *getRHistogram() { return r_histogram; }
	const int *getGHistogram() { return g_histogram; }
	const int *getBHistogram() { return b_histogram; }
	const int *getGrayHistogram() { return gray_histogram; }
private:
	int r_histogram[255];
	int g_histogram[255];
	int b_histogram[255];
	int gray_histogram[255];
};

#endif /* _HISTOGRAM_H_ */
