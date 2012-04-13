#ifndef _SLIDERPANEL_H_
#define _SLIDERPANEL_H_

#include <QWidget>

class QSlider;
class QSpinBox;
class QLabel;

class SliderPanel : public QWidget {
	Q_OBJECT
public:
	SliderPanel(QWidget *parent);
	SliderPanel(const QString &str = "", QWidget *parent = 0);
	int getValue();
	void setMaximum(int value);
	void setMinimum(int value);
	void setRange(int min, int max);
signals:
	void valueChanged(int value);
public slots:
	void setValue(int value);
private slots:
	void updateValue(int value);
private:
	QSlider *slider;
	QLabel *label;
	QSpinBox *spinBox;
};

#endif /* _SLIDERPANEL_H_ */
