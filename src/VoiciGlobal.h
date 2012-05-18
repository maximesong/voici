#ifndef _VOICIGLOBAL_H_
#define _VOICIGLOBAL_H_

#include <QImage>

class VoiciMainWindow;

extern VoiciMainWindow *mainWindow;

const int MAX_PIXEL_VALUE = 255;

const double PI = 3.1415;

enum ColorChannel { RED, GREEN, BLUE, GRAY };

const char acceptImageLabel[] = "All Images (*.png *.jpg *.gif *.bmp);;" 
	"PNG Image (*.png);;"
	"JPG Image (*.jpg);;"
	"GIF Image (*.gif);;"
	"BMP Image (*.bmp);;"
	"All Files (*.*);;";

inline int legalized_level(int level)
{
	if (level > MAX_PIXEL_VALUE)
		return MAX_PIXEL_VALUE;
	if (level < 0)
		return 0;
	return level;
}

inline int bytes_num(const QImage &image)
{
	return image.depth() / 8;
}

const int PRE_PROCESSER_NR = 10;

const int POST_PROCESSER_NR = 10;

const int  BILINEAR_SHIFT = 4;

enum PreProcesser { Graying };

enum PostProcesser { Thresholding, Scale, Rotate, Selection };

#endif /* _VOICIGLOBAL_H_ */
