#ifndef _VOICIGLOBAL_H_
#define _VOICIGLOBAL_H_


const int MAX_PIXEL_VALUE = 255;

const double PI = 3.1415;

enum ColorChannel { RED, GREEN, BLUE, GRAY };

const char acceptImageLabel[] = "Image Files (*.png *.jpg *.bmp)";

inline int legalized_level(int level)
{
	if (level > MAX_PIXEL_VALUE)
		return MAX_PIXEL_VALUE;
	if (level < 0)
		return 0;
	return level;
}

const int PRE_PROCESSER_NR = 10;

const int POST_PRECESSER_NR = 10;

enum PreProcesser { Graying };

enum PostProcesser { Thresholding };

#endif /* _VOICIGLOBAL_H_ */
