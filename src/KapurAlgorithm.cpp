#include "KapurAlgorithm.h"

#include <cmath>
#include <iostream>
using namespace std;

#include "VoiciGlobal.h"
#include "Histogram.h"

int KapurAlgorithm::computeThreshold(const Histogram &histogram)
{
	int threshold = 0;
	double max_evaluation = computeEvaluation(histogram, 0);
	for (int i = 2; i <= MAX_PIXEL_VALUE; ++i) {
		double evaluation = computeEvaluation(histogram, i);
		if (evaluation > max_evaluation) {
			threshold = i;
			max_evaluation = evaluation;
		}
	}
	return threshold;
}

double KapurAlgorithm::computeEvaluation(const Histogram &histogram, 
					 int threshold)
{
	double p_t = histogram.getAccumulateWeight(threshold, GREEN);
	if (p_t == 0 || p_t == 1)
		return -1000000;
	double h_t = 0;
	for (int i = 0; i <= threshold; ++i) {
		double weight = histogram.getWeight(i, GREEN);
		if (weight != 0)
			h_t += -log(weight) * weight;
	}
	double h_l = 0;
	for (int i = 0; i <= MAX_PIXEL_VALUE; ++i) {
		double weight = histogram.getWeight(i, GREEN);
		if (weight != 0)
			h_l += -log(weight) * weight;
	}
	double value = log(p_t) * (1 - p_t) + h_t / p_t + 
		(h_l - h_t) / (1 - p_t);
	return value;
}
