#ifndef _HISTOGRAM_H_
#define _HISTOGRAM_H_

#include "VoiciGlobal.h"

class QImage;

class Histogram {
public:

	Histogram(const QImage &image, double r = 11 / 32.0, double g = 16 / 32.0,
		  double b = 5 / 32.0);

	void loadImage(const QImage &image);
	void setRate(double r, double g, double b);
	int getCount(int i, ColorChannel type) const;
	int getAccumulateCount(int i, ColorChannel type) const;
	int getCount(int from, int to, ColorChannel type) const;
	double getWeight(int i, ColorChannel type) const;
	double getAccumulateWeight(int i, ColorChannel type) const;
	double getWeight(int from, int to, ColorChannel type) const;
	double getMeanIntensity(int from, int to, ColorChannel type) const;
private:
	const int *getHistogram(ColorChannel type) const;
	const int *getAccumulateHistogram(ColorChannel type) const;
	int r_histogram[MAX_PIXEL_VALUE + 1];
	int r_accululate_histogram[MAX_PIXEL_VALUE + 1];
	int g_histogram[MAX_PIXEL_VALUE + 1];
	int g_accumulate_histogram[MAX_PIXEL_VALUE + 1];
	int b_histogram[MAX_PIXEL_VALUE + 1];
	int b_accumulate_histogram[MAX_PIXEL_VALUE + 1];
	int gray_histogram[MAX_PIXEL_VALUE + 1];
	int gray_accumulate_histogram[MAX_PIXEL_VALUE + 11];
	double r_rate;
	double g_rate;
	double b_rate;
	int total_weight;
};

#endif /* _HISTOGRAM_H_ */
