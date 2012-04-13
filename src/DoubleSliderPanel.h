#ifndef _DOUBLESLIDERPANEL_H_
#define _DOUBLESLIDERPANEL_H_

#include <QWidget>

class QSlider;
class QDoubleSpinBox;
class QLabel;

class DoubleSliderPanel : public QWidget {
	Q_OBJECT
public:
	DoubleSliderPanel(QWidget *parent);
	DoubleSliderPanel(const QString &str = "", QWidget *parent = 0);
	int getValue();
	void setMaximum(double value);
	void setMinimum(double value);
	void setRange(double min, double max);
signals:
	void valueChanged(double value);
public slots:
	void setValue(double value);
private slots:
	void updateValue(int value);
	void updateValue(double value);
private:
	QSlider *slider;
	QLabel *label;
	QDoubleSpinBox *spinBox;
};


#endif /* _DOUBLESLIDERPANEL_H_ */
