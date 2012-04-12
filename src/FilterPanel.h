#ifndef _FILTERPANEL_H_
#define _FILTERPANEL_H_

#include <QWidget>

class QPushButton;
class ImageProcess;
class QDoubleSpinBox;
class QSpinBox;

class FilterPanel : public QWidget {
	Q_OBJECT
public:
	FilterPanel(QWidget *parent = 0);
//	virtual ~FilterPanel();
	
signals:
	void newProcess(ImageProcess *process);
public slots:
	void addGaussProcess();
	void addMeanFilterProcess();
	void addMedianFilterProcess();
private:
	QPushButton *quickGaussBlurButton;
	QDoubleSpinBox *gaussHorizontalBox;
	QDoubleSpinBox *gaussVerticalBox;

	QSpinBox *rowCountBox;
	QSpinBox *columnCountBox;
	QPushButton *meanFilterButton;
	QPushButton *medianFilterButton;
};

#endif /* _FILTERPANEL_H_ */
