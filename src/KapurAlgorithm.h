#ifndef _KAPURALGORITHM_H_
#define _KAPURALGORITHM_H_

class Histogram;

class KapurAlgorithm {
public:
	static int computeThreshold(const Histogram &Histogram);
private:
	static double computeEvaluation(const Histogram &Histogram, 
					int threshold);
};

#endif /* _KAPURALGORITHM_H_ */
