#ifndef _VOICIGLOBAL_H_
#define _VOICIGLOBAL_H_

const int MAX_PIXEL_VALUE = 255;

enum ColorChannel { RED, GREEN, BLUE, GRAY };

inline int legalized_level(int level)
{
	if (level > MAX_PIXEL_VALUE)
		return MAX_PIXEL_VALUE;
	if (level < 0)
		return 0;
	return level;
}

#endif /* _VOICIGLOBAL_H_ */
