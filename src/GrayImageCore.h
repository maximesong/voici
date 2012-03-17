#ifndef _GRAYIMAGECORE_H_
#define _GRAYIMAGECORE_H_

#include "ImageCore.h"
#include <QObject>

class GrayImageCore : public ImageCore {
	Q_OBJECT
public:
	GrayImageCore(const QString &id = "");
/*	GrayImageCore(const ImageCore &imageCore); */
	~GrayImageCore();
public slots:
	void setColorfulImage(const ImageCore& imageCore);
private:
	ImageProcess *grayProcess;
};


#endif /* _GRAYIMAGECORE_H_ */
