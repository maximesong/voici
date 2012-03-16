#ifndef _THRESHOLDPANEL_H_
#define _THRESHOLDPANEL_H_

#include <QWidget>

class ThresholdPanel : public QWidget
{
	Q_OBJECT
public:
	ThresholdPanel(QWidget *parent = 0);
signals:
	void lowBoundChanged(int low);
	void highBoundChanged(int high);
};


#endif /* _THRESHOLDPANEL_H_ */
