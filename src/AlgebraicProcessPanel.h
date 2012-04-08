#ifndef _ALGEBRAICPROCESSPANEL_H_
#define _ALGEBRAICPROCESSPANEL_H_

#include <QWidget>

class PreviewCanvas;
class QPushButton;

class AlgebraicProcessPanel : public QWidget {
	Q_OBJECT
public:
	AlgebraicProcessPanel(QWidget *parent = 0);
//	virtual ~AlgebraicProcessPanel();
signals:
		
public slots:
	void selectImage();
private:
	PreviewCanvas *opImageCanvas;
	QPushButton *selectImageButton;
	QPushButton *imageAddButton;
	QPushButton *imageSubstractButton;
	QPushButton *imageProductButton;
	QPushButton *imageQuotientButton;
};

#endif /* _ALGEBRAICPROCESSPANEL_H_ */
