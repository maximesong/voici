#ifndef _IMAGE_CORE_H
#define _IMAGE_CORE_H

#include <QVector>
#include <QObject>
#include <QString>
#include <QImage>

#include "Histogram.h"

class ImageCore : public QObject {
	Q_OBJECT
public:
	ImageCore(const QString &name = "");
	~ImageCore();

	void load(const QString &filename);

	const QImage &getImage() const { return m_image; }

	Histogram getHistogram() const { return Histogram(this->getImage()); }

	const QString &getName() const { return m_name; }

signals:
	void imageChanged(const ImageCore& imageCore);
private:
	QImage m_image;
	QString m_name;
};

#endif
