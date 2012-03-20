#ifndef _MATRIXBLOCKMAP_H_
#define _MATRIXBLOCKMAP_H_

#include <QImage>

#include "BlockMap.h"

class MatrixBlockMap : public BlockMap {
public:
	MatrixBlockMap(int m, int n, double *matrix);
	~MatrixBlockMap();
	virtual QRgb map(int x_offset, int y_offset, QImage *image);
private:
	int getGrayDegree(int i, int j, QImage *image);
	int m_m;
	int m_n;
	double *m_matrix;
};

#endif /* _MATRIXBLOCKMAP_H_ */
