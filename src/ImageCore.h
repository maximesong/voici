#ifndef _IMAGE_CORE_H
#define _IMAGE_CORE_H

#include <QVector>

class ImageCore : QObject {
	Q_OBJECT
public:
	ImageCore();
	~ImageCore();

	void load(const QString &filename);
	const QImage &getImage() const { return m_image; }
signals:
	void imageChanged();
private:
	QImage m_image;
	Histogram *histogram;
};

#endif
