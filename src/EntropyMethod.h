#ifndef _ENTROPYMETHOD_H_
#define _ENTROPYMETHOD_H_

class Histogram;

class EntropyMethod {
public:
	static int computeThreshold(const Histogram &histogram);
private:
	static double computeEvaluation(const Histogram &histogram, int threshold);
};

#endif /* _ENTROPYMETHOD_H_ */
