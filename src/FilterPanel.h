#ifndef _FILTERPANEL_H_
#define _FILTERPANEL_H_

#include <QWidget>

class QPushButton;
class ImageProcess;
class QDoubleSpinBox;

class FilterPanel : public QWidget {
	Q_OBJECT
public:
	FilterPanel(QWidget *parent = 0);
//	virtual ~FilterPanel();
	
signals:
	void newProcess(ImageProcess *process);
public slots:
	void addGaussProcess();
private:
	QPushButton *quickGaussBlurButton;
	QDoubleSpinBox *gaussHorizontalBox;
	QDoubleSpinBox *gaussVerticalBox;
};

#endif /* _FILTERPANEL_H_ */
