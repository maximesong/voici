#ifndef _MEDIANBLOCKMAP_H_
#define _MEDIANBLOCKMAP_H_

#include "BlockMap.h"

class MedianBlockMap : public BlockMap {
public:
	MedianBlockMap(int m, int n);
	virtual QRgb map(int x_offset, int y_offset, const QImage *image);
private:
	int m_m;
	int m_n;
};

#endif /* _MEDIANBLOCKMAP_H_ */
