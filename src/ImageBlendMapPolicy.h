#ifndef _IMAGEBLENDMAPPOLICY_H_
#define _IMAGEBLENDMAPPOLICY_H_

class ImageBlendMapPolicy {
public:
	virtual int channelBlend(int firstLevel, int secondLevel) = 0;
};

#endif /* _IMAGEBLENDMAPPOLICY_H_ */
