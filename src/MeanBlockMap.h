#ifndef _MEANBLOCKMAP_H_
#define _MEANBLOCKMAP_H_

#include "BlockMap.h"

class MeanBlockMap : public BlockMap {
public:
	MeanBlockMap(int m, int n);
	virtual QRgb map(int x_offset, int y_offset, QImage *image);
private:
	int m_m;
	int m_n;
};

#endif /* _MEANBLOCKMAP_H_ */
