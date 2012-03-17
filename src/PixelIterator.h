#ifndef _PIXELITERATOR_H_
#define _PIXELITERATOR_H_

class QImage;
class PixelMap;

class PixelIterator {
public:
	static void iterate(QImage *image, PixelMap *map);
};

#endif /* _PIXELITERATOR_H_ */
