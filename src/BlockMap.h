#ifndef _BLOCKMAP_H_
#define _BLOCKMAP_H_

#include <QImage>

class BlockMap {
public:
	virtual QRgb map(int x_offset, int y_offset, QImage *image) = 0;
};

#endif /* _BLOCKMAP_H_ */
