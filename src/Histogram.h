#ifndef _HISTOGRAM_H_
#define _HISTOGRAM_H_

#include "VoiciGlobal.h"

class QImage;

class Histogram {
public:
	enum ColorChannel { Red, Green, Blue, Gray };

	Histogram(const QImage &image, double r = 11 / 32.0, double g = 16 / 32.0,
		  double b = 5 / 32.0);

	void loadImage(const QImage &image);
	void setRate(double r, double g, double b);
	int getCount(int i, ColorChannel type) const;
	int getCount(int from, int to, ColorChannel type) const;
	double getWeight(int i, ColorChannel type) const;
	double getWeight(int from, int to, ColorChannel type) const;
	double getMeanIntensity(int from, int to, ColorChannel type) const;
private:
	const int *getHistogram(ColorChannel type) const;
	int r_histogram[MAX_PIXEL_VALUE];
	int g_histogram[MAX_PIXEL_VALUE];
	int b_histogram[MAX_PIXEL_VALUE];
	int gray_histogram[MAX_PIXEL_VALUE];
	double r_rate;
	double g_rate;
	double b_rate;
	int total_weight;
};

#endif /* _HISTOGRAM_H_ */
