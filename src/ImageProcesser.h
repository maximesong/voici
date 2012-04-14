#ifndef _IMAGEPROCESSER_H_
#define _IMAGEPROCESSER_H_

#include <QSharedPointer>
#include <QString>

class QImage;

class ImageProcesser {
public:
	ImageProcesser(const QString &processerName);

	void setProcesserName(const QString &name);

	QString getProcesserName() const;

	virtual QImage produceProcessedImage(const QImage &image) = 0;
private:
	QString m_processer_name;
};

typedef QSharedPointer<ImageProcesser> SharedImageProcessor;

#endif /* _IMAGEPROCESSER_H_ */
