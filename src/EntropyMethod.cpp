#include "EntropyMethod.h"

#include <cmath>

#include "VoiciGlobal.h"
#include "Histogram.h"

int EntropyMethod::computeThreshold(const Histogram &histogram)
{
	int threshold = 0;
	double max_evaluation = computeEvaluation(histogram, 0);
	for (int i = 1; i <= MAX_PIXEL_VALUE; ++i) {
		double evaluation = computeEvaluation(histogram, i);
		if (evaluation > max_evaluation) {
			threshold = i;
			max_evaluation = evaluation;
		}
	}
	return threshold;
}

double EntropyMethod::computeEvaluation(const Histogram &histogram, int threshold)
{
	double h1 = 0;
	double weight1 = histogram.getWeight(0, threshold, GRAY);
	for (int i = 0; i <= threshold; ++i) {
		double weight = histogram.getWeight(i, GRAY) / weight1;
		h1 += log(weight) * weight;
	}
	double h2 = 0;
	double weight2 = histogram.getWeight(threshold + 1, MAX_PIXEL_VALUE, GRAY);
	for (int i = threshold + 1; i <= MAX_PIXEL_VALUE; ++i) {
		double weight = histogram.getWeight(i, GRAY) / weight2;
		h2 += log(weight) * weight;
	}
	return -(h1 + h2);
}
