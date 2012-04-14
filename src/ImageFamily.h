#ifndef _IMAGEFAMILY_H_
#define _IMAGEFAMILY_H_

#include <QVector>
#include <QObject>
#include <QString>
#include <QImage>
#include <QSharedPointer>

#include "Process.h"

class ImageFamily : public QObject {
	Q_OBJECT
public:
	ImageFamily(const QImage &originImage, const QString &familyName = "");
	ImageFamily(const QString &originImageFilename, const QString &familyName = "");
//	ImageFamily(const ImageFamily &imageFamily);
//	ImageCore &operator=(const ImageFamily &imageFamily);

	QImage getOriginImage() const;

	QImage getCurrentImage() const;

	QString getFamilyName() const;

	QString getDynamicProcesserName(int index) const;

signals:
	void currentImageChanged(const ImageFamily& imageFamily);

public slots:
	virtual void loadOriginImage(const QString &filename);

	virtual void setOriginImage(const QImage &image);

	void setFamilyName(const QString &name);

	void pushDynamicImageProcesser(SharedImageProcessor processer);

	void popDynamicImageProcesser();

	void switchToDynamicProcess(int index);

private:
	virtual void applyDynamicProcessers();
	virtual void applyPostProcessers();
	virtual void applyPreProcessers();
	virtual void applyAllProcessers(bool needApplyPreProcessers = 0);
	void initFamily();

	QString m_family_name;
	QVector<SharedImageProcessor> m_dynamic_processer_list;
	QVector<SharedImageProcessor> m_pre_processer_list;
	QVector<SharedImageProcessor> m_post_processer_list;
	QImage m_origin_image;
	QImage m_pre_processed_image;
	QVector<QImage> m_dynamic_image_list;
	QImage m_dynamic_image;
	QImage m_post_processed_image;
	int m_dynamic_processer_index;
};

#endif /* _IMAGEFAMILY_H_ */
