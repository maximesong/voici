#ifndef _IMAGEUTILITY_H_
#define _IMAGEUTILITY_H_

#include <QImage>

class ImageUtility {
public:
	static void getRow(const QImage &image, uchar *buf,
			   int x, int y, int width);

	static void getColumn(const QImage &image, uchar *buf,
			      int x, int y, int height);

	static void setRow(QImage &image, const uchar *buf,
			   int x, int y, int width);

	static void setColumn(QImage &image, const uchar *buf,
			      int x, int y, int height);
};

#endif /* _IMAGEUTILITY_H_ */
