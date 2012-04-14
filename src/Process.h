#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <QSharedPointer>

#include "ImageProcesser.h"

class ImageFamily;

class ImageFamilyProcess {
public:
	ImageFamilyProcess(const QString &processName = "");

	virtual QString getProcessName() const;

	virtual void setProcessName(const QString name);

	virtual void applyToImageFamily(ImageFamily *imageFamily) = 0;
private:
	QString m_process_name;
};

typedef QSharedPointer<ImageFamilyProcess> SharedProcess;


class DynamicImageProcess : public ImageFamilyProcess {
public:
	DynamicImageProcess(SharedImageProcessor imageProcessor,
			    const QString &processName = "");

	virtual void applyToImageFamily(ImageFamily *imageFamily);
private:
	SharedImageProcessor m_image_processer;
};

#endif /* _PROCESS_H_ */
