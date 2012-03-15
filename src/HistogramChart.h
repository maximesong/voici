#ifndef _HISTOGRAMCHART_H_
#define _HISTOGRAMCHART_H_

#include <QWidget>

#include "Histogram.h"

class ImageCore;

class HistogramChart : public QWidget
{
	Q_OBJECT
public:
	HistogramChart(QWidget * parent);
public slots:
	void drawChart(const ImageCore &imageCore);
	void setLowThreshold(int low);
	void setHighThreshold(int high);
protected:
	virtual void paintEvent(QPaintEvent *event);
private:
	Histogram m_histogram;
	int m_low;
	int m_high;
};


#endif /* _HISTOGRAMCHART_H_ */
