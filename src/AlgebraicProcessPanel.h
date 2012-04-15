#ifndef _ALGEBRAICPROCESSPANEL_H_
#define _ALGEBRAICPROCESSPANEL_H_

#include <QWidget>
#include <QImage>

#include "Process.h"

class PreviewCanvas;
class QPushButton;

class AlgebraicProcessPanel : public QWidget {
	Q_OBJECT
public:
	AlgebraicProcessPanel(QWidget *parent = 0);
//	virtual ~AlgebraicProcessPanel();
signals:
	void newProcess(SharedProcess process);
public slots:
	void selectImage();
	void sendAddProcess();
	void sendSubstractProcess();
	void sendProductProcess();
	void sendQuotientProcess();
private:
	PreviewCanvas *opImageCanvas;
	QPushButton *selectImageButton;
	QPushButton *imageAddButton;
	QPushButton *imageSubstractButton;
	QPushButton *imageProductButton;
	QPushButton *imageQuotientButton;
	QImage previewImage;
};

#endif /* _ALGEBRAICPROCESSPANEL_H_ */
