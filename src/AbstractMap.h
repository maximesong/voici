#ifndef _ABSTRACTMAP_H_
#define _ABSTRACTMAP_H_

#include <QImage>

class PositionalByteMap {
public:
	virtual uchar map(uchar src, int x, int y) = 0;
};


class ByteMap : public PositionalByteMap {
public:
	virtual uchar map(uchar src, int x, int y);
	virtual uchar map(uchar src) = 0;
};


class PositionalRgbMap {
public:
	virtual QRgb map(uchar r, uchar g, uchar b, uchar a, int x, int y) = 0;
};


class RgbMap {
public:
	virtual QRgb map(uchar r, uchar g, uchar b, uchar a, int x, int y);
	virtual QRgb map(uchar r, uchar g, uchar b, uchar a) = 0;
};


class AreaRgbMap {
public:
	virtual QRgb map(const QImage *image, int x, int y) = 0;
};

#endif /* _ABSTRACTMAP_H_ */
