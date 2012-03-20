#include "MatrixBlockMap.h"

MatrixBlockMap::MatrixBlockMap(int m, int n, double *matrix)
{
	m_m = m;
	m_n = n;
	m_matrix = matrix;
}


MatrixBlockMap::~MatrixBlockMap()
{
	delete m_matrix;
}

QRgb MatrixBlockMap::map(int x_offset, int y_offset, QImage *image)
{
	double sum = 0;
	for (int i = 0; i != m_m; ++i)
		for (int j = 0; j !=  m_n; ++j)
			sum += getGrayDegree(x_offset + i, y_offset + j, image) * 
				m_matrix[i + j * m_m];
	int gray = int(sum);
	return qRgb(gray, gray, gray);
}

/* Assume this is a gray image, and r == g == b */
int MatrixBlockMap::getGrayDegree(int i, int j, QImage *image)
{
	QRgb rgb = image->pixel(i, j);
	return qRed(rgb);
}
