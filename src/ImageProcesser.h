#ifndef _IMAGEPROCESSER_H_
#define _IMAGEPROCESSER_H_

#include <QSharedPointer>
#include <QString>

#include "Map.h"
#include "Iterator.h"

class ImageProcesser {
public:
	ImageProcesser(const QString &processerName = "");

	void setProcesserName(const QString &name);

	QString getProcesserName() const;

	virtual QImage produceProcessedImage(const QImage &src) = 0;
private:
	QString m_processer_name;
};

typedef QSharedPointer<ImageProcesser> SharedImageProcessor;


class RgbImageProcesser : public ImageProcesser {
public:
	RgbImageProcesser(Iterator *iter, PositionalRgbMap *map,
			  const QString &processerName  = "");
	~RgbImageProcesser();
	virtual QImage produceProcessedImage(const QImage &src);
private:
	Iterator *m_iter;
	PositionalRgbMap *m_map;
};

class ByteImageProcesser : public ImageProcesser {
public:
	ByteImageProcesser(Iterator *iter, PositionalByteRgbMap *map,
			  const QString &processerName  = "");
	~ByteImageProcesser();
	virtual QImage produceProcessedImage(const QImage &src);
private:
	Iterator *m_iter;
	PositionalByteMap *m_map;
};

class AreaRgbImageProcesser : public ImageProcesser {
	AreaRgbImageProcesser(Iterator *iter, AreaRgbMap *map,
			  const QString &processerName  = "");
	~AreaRgbImageProcesser();
	virtual QImage produceProcessedImage(const QImage &src);
private:
	Iterator *m_iter;
	AreaRgbMap *m_map;
};

#endif /* _IMAGEPROCESSER_H_ */
