#ifndef _OTSUALGORITHM_H_
#define _OTSUALGORITHM_H_

class Histogram;

class OtsuAlgorithm {
public:
	static int computeThreshold(const Histogram &histogram);
private:
	static double computeEvaluation(const Histogram &histogram, int threshold);
};

#endif /* _OTSUALGORITHM_H_ */
