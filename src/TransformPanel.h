#ifndef _TRANSFORMPANEL_H_
#define _TRANSFORMPANEL_H_

#include <QWidget>

class ImageProcess;

class TransformPanel : public QWidget {
	Q_OBJECT
public:
	TransformPanel(QWidget *parent = 0);
//	virtual ~TransformPanel();
	
signals:
	void newProcess(ImageProcess *process);
public slots:
	
private:
};

#endif /* _TRANSFORMPANEL_H_ */
