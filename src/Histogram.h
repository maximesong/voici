#ifndef _HISTOGRAM_H
#define _HISTOGRAM_H

class Histogram {
public:
	Histogram();
	void computeHistogram(const QImage &image);
	void setBlendRate(double r, double g, double b);
private:
	double rRate;
	double gRate;
	double bRate;
	int r_histogram[255];
	int g_histogram[255];
	int b_histogram[255];
	int gray_histogram[255];
};

#endif
