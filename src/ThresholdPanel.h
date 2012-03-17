#ifndef _THRESHOLDPANEL_H_
#define _THRESHOLDPANEL_H_

#include <QWidget>

class ThresholdPanel : public QWidget
{
	Q_OBJECT
public:
	ThresholdPanel(QWidget *parent = 0);
signals:
	void thresholdChanged(int low, int high);
private slots:
	void setLow(int low);
	void setHigh(int high);
	int getLow() { return m_low; }
	int getHigh() { return m_high; }
private:
	int m_low;
	int m_high;
};


#endif /* _THRESHOLDPANEL_H_ */
