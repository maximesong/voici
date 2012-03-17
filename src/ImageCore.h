#ifndef _IMAGE_CORE_H
#define _IMAGE_CORE_H

#include <QVector>
#include <QObject>
#include <QString>
#include <QImage>
#include <QVector>
#include <QSharedPointer>

#include "Histogram.h"
#include "ImageProcess.h"

class ImageCore : public QObject {
	Q_OBJECT
public:
	ImageCore(const QString &id = "");
	ImageCore(const ImageCore &imageCore);
	~ImageCore();

	ImageCore &operator=(const ImageCore &imageCore);

	static ImageCore toGrayImageCore(const ImageCore &imageCore);

	void load(const QString &filename);

	void setOriginImage(const QImage &image) { m_origin_image = image; }

	const QImage &getOriginImage() const { return m_origin_image; }

	void setCurrentImage(const QImage &image) { m_current_image = image; }

	const QImage &getCurrentImage() const { return m_current_image; }

	const QString &getId() const { return m_id; }

	void setId(const QString id) { m_id = id; }

	void pushImageProcess(ImageProcess *process);

	void goProcessN(int n);

	QString getProcessNameN(int n) { return m_processes[n]->getProcessName(); }

	void applyImageProcess(ImageProcess *process);

	void originToCurrent() { m_current_image = m_origin_image; }

	void currentToOrigin() { m_origin_image = m_current_image; }

signals:
	void imageChanged(const ImageCore& imageCore);
protected:
	QVector<QSharedPointer<ImageProcess> > m_processes;
	int m_current_process;
	QImage m_origin_image;
	QImage m_current_image;
	QString m_id;
};

#endif
