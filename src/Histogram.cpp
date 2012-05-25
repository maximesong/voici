#include "Histogram.h"

#include <QImage>

Histogram::Histogram(const QImage &image, double r, 
		     double g,  double b)
{
	setRate(r, g, b);
	loadImage(image);
}

void Histogram::setRate(double r, double g, double b)
{
	r_rate = r;
	g_rate = g;
	b_rate = b;
}

void Histogram::loadImage(const QImage &image)
{
	for (int i = 0; i <= MAX_PIXEL_VALUE; ++i) {
		r_histogram[i] = 0;
		g_histogram[i] = 0;
		b_histogram[i] = 0;
		gray_histogram[i] = 0;

		r_accululate_histogram[i] = 0;
		g_accumulate_histogram[i] = 0;
		b_accumulate_histogram[i] = 0;
		gray_accumulate_histogram[i] = 0;
	}

	for (int i = 0; i != image.width(); ++i)
		for (int j = 0; j != image.height(); ++j) {
			QRgb rgb = image.pixel(i, j);
			int r = qRed(rgb);
			int g = qGreen(rgb);
			int b = qBlue(rgb);
			++r_histogram[r];
			++g_histogram[g];
			++b_histogram[b];
			++gray_histogram[int(r * r_rate + g * g_rate + b * b_rate)];
		}
	total_weight = image.width() * image.height();

	r_accululate_histogram[0] = r_histogram[0];
	g_accumulate_histogram[0] = g_histogram[0];
	b_accumulate_histogram[0] = b_histogram[0];
	gray_accumulate_histogram[0] = gray_histogram[0];
	for (int i = 1; i != MAX_PIXEL_VALUE + 1; ++i) {
		r_accululate_histogram[i] = 
			r_accululate_histogram[i - 1] + r_histogram[i];
		g_accumulate_histogram[i] = 
			g_accumulate_histogram[i - 1] + g_histogram[i];
		b_accumulate_histogram[i] = 
			b_accumulate_histogram[i - 1] + b_histogram[i];
		gray_accumulate_histogram[i] = 
			gray_accumulate_histogram[i -1] + gray_histogram[i];
			
	}
}


int Histogram::getCount(int i, ColorChannel type) const
{
	const int *histogram = getHistogram(type);
	return histogram[i];
}

int Histogram::getAccumulateCount(int i, ColorChannel type) const
{
	const int *histogram = getAccumulateHistogram(type);
	return histogram[i];
}

int Histogram::getCount(int from, int to, ColorChannel type) const
{
	const int *histogram = getHistogram(type);
	int count = 0;
	for (int i = from; i <= to; ++i) {
		count += histogram[i];
	}
	return count;
}


double Histogram::getWeight(int i, ColorChannel type) const
{
	int count = getCount(i, type);
	return static_cast<double>(count) / total_weight;
}

double Histogram::getWeight(int from, int to, ColorChannel type) const
{
	int count = getCount(from, to, type);
	return static_cast<double>(count) / total_weight;
}

double Histogram::getAccumulateWeight(int i, ColorChannel type) const
{
	int count = getAccumulateCount(i, type) - getAccumulateCount(0, type);
	return static_cast<double>(count) / total_weight;
}

double Histogram::getMeanIntensity(int from, int to, ColorChannel type) const
{
	double mean_intensity = 0;
	for (int i = from; i <= to; ++i) {
		mean_intensity += i * getWeight(i, type);
	}
	return mean_intensity;
}

const int *Histogram::getHistogram(ColorChannel type) const 
{ 
	switch(type) {
	case RED:
		return r_histogram;
	case GREEN:
		return g_histogram;
	case BLUE:
		return b_histogram;
	case GRAY:
		return gray_histogram;
	default:
		return gray_histogram;
	}
}


const int *Histogram::getAccumulateHistogram(ColorChannel type) const 
{ 
	switch(type) {
	case RED:
		return r_accululate_histogram;
	case GREEN:
		return g_accumulate_histogram;
	case BLUE:
		return b_accumulate_histogram;
	case GRAY:
		return gray_accumulate_histogram;
	default:
		return gray_accumulate_histogram;
	}
}

