#include "OtsuAlgorithm.h"

#include "VoiciGlobal.h"
#include "Histogram.h"

#include <iostream>
using namespace std;

int OtsuAlgorithm::computeThreshold(const Histogram &histogram)
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

double OtsuAlgorithm::computeEvaluation(const Histogram &histogram, int threshold)
{
	double u1 = histogram.getMeanIntensity(0, threshold, GRAY);
	double w1 = histogram.getWeight(0, threshold, GRAY);
	double u2 = histogram.getMeanIntensity(threshold + 1, MAX_PIXEL_VALUE,
					GRAY);
	double w2 = histogram.getWeight(threshold + 1, MAX_PIXEL_VALUE,
					GRAY);
	if (w1 == 0.0 || w2 == 0.0)
		return 0.0;
	double u_diff = u1 / w1 - u2 / w2;

	return w1 * w2 * u_diff * u_diff;
}
