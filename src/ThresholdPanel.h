#ifndef _THRESHOLDPANEL_H_
#define _THRESHOLDPANEL_H_

#include <QWidget>

class SliderPanel;

class ThresholdPanel : public QWidget
{
	Q_OBJECT
public:
	ThresholdPanel(QWidget *parent = 0);
	int getLow();
	int getHigh();
signals:
	void thresholdChanged(int low, int high);
public slots:
	void setLow(int low);
	void setHigh(int high);
	void setThreshold(int low, int high);
private:
	SliderPanel *highSlider;
	SliderPanel *lowSlider;
};


#endif /* _THRESHOLDPANEL_H_ */
