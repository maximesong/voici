#ifndef _PIXELITERATOR_H_
#define _PIXELITERATOR_H_

class QImage;

class PixelMap;

class PixelIterator {
public:
	/* The negative value of width or height means infinite */
	PixelIterator(int x = 0, int y = 0, int width = -1, int height = -1);
	static void rawIterate(QImage *image, PixelMap *map);
	void iterate(QImage *image, PixelMap *map);
	void setRange(int x, int y, int width, int height);
	void setWidthAndHeight(int width, int height);
	void setStartPoint(int x, int y);
private:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
};

#endif /* _PIXELITERATOR_H_ */
