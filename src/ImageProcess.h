#ifndef _IMAGEPROCESS_H_
#define _IMAGEPROCESS_H_

#include <QString>

class QImage;
class ImageCore;

class ImageProcess {
public:
	ImageProcess(const QString processName = "Magic Process")
		: m_process_name(processName) { /* empty */ }
	
	virtual QString getProcessName() { return m_process_name; }

	virtual void processImage(ImageCore *imageCore);
protected:
	virtual QImage generateNewImage(const QImage &image) = 0;
private:
	QString m_process_name;
};


#endif /* _IMAGEPROCESS_H_ */