#ifndef _MATRIXBLOCKMAP_H_
#define _MATRIXBLOCKMAP_H_

#include <QImage>
#include <QVector>

#include "BlockMap.h"

class MatrixBlockMap : public BlockMap {
public:
	MatrixBlockMap(int m, int n, const QVector<double> &matrix);
	virtual QRgb map(int x_offset, int y_offset, const QImage *image);
private:
	int getGrayDegree(int i, int j, const QImage *image);
	int m_m;
	int m_n;
	QVector<double> m_matrix;
};

#endif /* _MATRIXBLOCKMAP_H_ */
