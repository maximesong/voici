#ifndef _GRAYIMAGECORE_H_
#define _GRAYIMAGECORE_H_

#include <QObject>

#include "ImageCore.h"

class GrayImageCore : public ImageCore {
	Q_OBJECT
public:
	GrayImageCore(const QString &id = "");
/*	GrayImageCore(const ImageCore &imageCore); */
	~GrayImageCore();
public slots:
	void setColorfulImage(const ImageCore& imageCore);
	void setThreshold(int low, int high);
protected:
	virtual void applyPreProcesses();
	virtual void applyPostProcesses();
private:
	ImageProcess *grayProcess;
	ImageProcess *binaryProcess;
};


#endif /* _GRAYIMAGECORE_H_ */
