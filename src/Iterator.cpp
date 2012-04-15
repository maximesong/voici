#include "Iterator.h"

Iterator::Iterator(IteratorArea *area)
{
	m_area = area;
}

Iterator::~Iterator()
{
	delete m_area;
}

void Iterator::rgbIterate(QImage *dest, const QImage *src, PositionalRgbMap *map)
{
	int start_x, start_y, end_x, end_y;
	if (m_area != 0) {
		if (m_area->startX() >= dest->width() || 
		    m_area->startY() >= dest->height())
			return;
		start_x = m_area->startX();
		start_y = m_area->startY();
		end_x = qMin(m_area->endX(), dest->width());
		end_y = qMin(m_area->endY(), dest->height());
	} else {
		start_x = 0;
		start_y = 0;
		end_x = dest->width();
		end_y = dest->height();
	}

	/* This may need to be fixed for non-rgba image */
	const QRgb *src_ptr = (const QRgb *) src->constBits();
	const QRgb *src_x, *src_y;
	QRgb *dest_ptr = (QRgb *) dest->bits();
	QRgb *dest_x, *dest_y;

	for (int j = start_y; j < end_y; ++j) {
		src_y = src_ptr + j * src->width();
		dest_y = dest_ptr + j * dest->width();
		for (int i = start_x; i < end_x; ++i) {
			if (m_area != 0 && ! m_area->inside_contains(i, j))
				continue;
			src_x = src_y + i;
			dest_x = dest_y + i;
			QRgb src_value = *src_x;
			QRgb map_value = map->map(qRed(src_value), qGreen(src_value),
						  qBlue(src_value), qAlpha(src_value),
						  i, j);
			memcpy(dest_x, &map_value, sizeof(QRgb));
		}
	}
}

void Iterator::byteIterate(QImage *dest, const QImage *src, PositionalByteMap *map)
{
	int start_x, start_y, end_x, end_y;
	if (m_area != 0) {
		if (m_area->startX() >= dest->width() || 
		    m_area->startY() >= dest->height())
			return;
		start_x = m_area->startX();
		start_y = m_area->startY();
		end_x = qMin(m_area->endX(), dest->width());
		end_y = qMin(m_area->endY(), dest->height());
	} else {
		start_x = 0;
		start_y = 0;
		end_x = dest->width();
		end_y = dest->height();
	}

	int bytes = dest->depth() / 8;
	int start_byte = 0;
	if (bytes == 4)
		start_byte = 1;

	const uchar *src_ptr = src->constBits();
	const uchar *src_x, *src_y;
	uchar *dest_ptr = dest->bits();
	uchar *dest_x, *dest_y;

	/* This may need to be fixed for non-rgba image */
	for (int byte = start_byte; byte != bytes; ++byte) {
		for (int j = start_y; j != end_y; ++j) {
			src_y = src_ptr + j * bytes * src->width();
			dest_y = dest_ptr + j * bytes * dest->width();
			for (int i = start_x; i != end_x; ++i) {
				if (m_area != 0 && ! m_area->inside_contains(i, j))
					continue;
				int offset = i * bytes  + byte;
				src_x = src_y + offset;
				dest_x = dest_y + offset;
				uchar map_value = map->map(*src_x, i, j);
				memcpy(dest_x, &map_value, sizeof(uchar));
			}
		}
	}
}

AreaIterator::AreaIterator(int m, int n, int x, int y, IteratorArea *area)
{
	m_m = m;
	m_n = n;
	m_x = x;
	m_y = y;
	m_rx_offset = x - m_m;
	m_ry_offset = y - m_n;
	m_area = area;
}

void AreaIterator::areaIterate(QImage *dest, const QImage *src, AreaRgbMap *map)
{
	int start_x, start_y, end_x, end_y;
	if (m_area != 0) {
		if (m_area->startX() >= dest->width() || 
		    m_area->startX() >= dest->height())
			return;
		start_x = qMax(m_area->startX() - m_rx_offset, m_m - 1);
		start_y = qMax(m_area->startY() - m_ry_offset, m_n - 1);;
		end_x = qMin(m_area->endX() - m_rx_offset, dest->width());
		end_y = qMin(m_area->endY() - m_ry_offset, dest->height());
	} else {
		start_x = m_m - 1;
		start_y = m_n - 1;
		end_x = dest->width();
		end_y = dest->height();
	}

	/* here i and j represents the right and bottom border of the matrix area */
	for (int j = start_y; j < end_y; ++j)
		for (int i = start_x; i < end_x; ++i) {
			if (m_area != 0 && ! m_area->inside_contains(i + m_rx_offset, 
								     j + m_ry_offset))
				continue;
			QRgb rgb = map->map(src, i - m_m + 1, j- m_n + 1);
			dest->setPixel(i + m_rx_offset, j + m_ry_offset, rgb);
		}
}
