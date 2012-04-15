#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include <QImage>

#include "IteratorArea.h"
#include "Map.h"

class Iterator {
public:
	Iterator(IteratorArea *area = 0);
	~Iterator();
 	virtual void byteIterate(QImage *dest, const QImage *src, 
				 PositionalByteMap *map);
	virtual void rgbIterate(QImage *dest, const QImage *src, 
				PositionalRgbMap *map);
protected:
	IteratorArea *m_area;
};


class AreaIterator : public Iterator {
public:
	AreaIterator(int m, int n, int x, int y, IteratorArea *area = 0);
	virtual void areaIterate(QImage *dest, const QImage *src, AreaRgbMap *map);
private:
	int m_m;
	int m_n;
	int m_x;
	int m_y;
	int m_rx_offset;
	int m_ry_offset;
};

#endif /* _ITERATOR_H_ */
