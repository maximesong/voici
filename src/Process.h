#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <QSharedPointer>

#include "ImageProcesser.h"

#include "VoiciGlobal.h"

class ImageFamily;

class ImageFamilyProcess {
public:
	ImageFamilyProcess(const QString &processName = "");

	virtual QString getProcessName() const;

	virtual void setProcessName(const QString &name);

	virtual void applyToImageFamily(ImageFamily *imageFamily) = 0;
private:
	QString m_process_name;
};

typedef QSharedPointer<ImageFamilyProcess> SharedProcess;


class DynamicImageProcess : public ImageFamilyProcess {
public:
	DynamicImageProcess(SharedImageProcessor imageProcesser,
			    const QString &processName = "");

	virtual void applyToImageFamily(ImageFamily *imageFamily);

	void setProcesser(SharedImageProcesser processer);
private:
	SharedImageProcessor m_image_processer;
};


class PreImageProcess : public ImageFamilyProcess {
	PreImageProcess(PreProcesser id, SharedImageProcessor imageProcesser,
			const QString &processName = "");
	virtual void applyToImageFamily(ImageFamily *imageFamily);

	void setPreProcesser(PreProcesser id, SharedImageProcesser processer);
private:
	SharedImageProcessor m_image_processer;
	PreProcesser m_id;
};

class PostImageProcess : public ImageFamilyProcess {
	PostImageProcess(PostProcesser id, SharedImageProcessor imageProcessor,
			const QString &processName = "");
	virtual void applyToImageFamily(ImageFamily *imageFamily);

	void setPostProcesser(PostProcesser id, SharedImageProcesser processer);
private:
	SharedImageProcessor m_image_processer;
	PostProcesser m_id;
};

#endif /* _PROCESS_H_ */
