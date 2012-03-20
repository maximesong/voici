#ifndef _BLOCKITERATOR_H_
#define _BLOCKITERATOR_H_

class QImage;

class BlockMap;

class BlockIterator {
public:
	/* m is the width of the matrix, n is the height,
	 * x and y starts from 1
	 */
	BlockIterator(int m, int n, int x, int y);

	void iterate(QImage *image, BlockMap *map);
private:
	int m_m;
	int m_n;
	int m_x;
	int m_y;
	int rx_offset;
	int ry_offset;
};

#endif /* _BLOCKITERATOR_H_ */
