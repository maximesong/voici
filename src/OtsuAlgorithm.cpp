#include "OtsuAlgorithm.h"

#include "VoiciGlobal.h"
#include "Histogram.h"

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
	double u1 = histogram.getMeanIntensity(0, threshold, Gray);
	double w1 = histogram.getWeight(0, threshold, Gray);
	double u2 = histogram.getMeanIntensity(threshold + 1, MAX_PIXEL_VALUE,
					Gray);
	double w2 = histogram.getWeight(threshold + 1, MAX_PIXEL_VALUE,
					Gray);
	double u_diff = u1 - u2;
	return w1 * w2 * u_diff * u_diff;
}
