#ifndef _HISTOGRAMCHART_H_
#define _HISTOGRAMCHART_H_

#include <QWidget>

#include "Histogram.h"

#include "ImageFamily.h"

class HistogramChart : public QWidget
{
	Q_OBJECT
public:
	HistogramChart(QWidget * parent = 0);
	Histogram getHistogram() { return m_histogram; }
public slots:
	void drawChart(const ImageFamily &imageCore);
	void setLowThreshold(int low);
	void setHighThreshold(int high);
	void setThreshold(int low, int high);
protected:
	virtual void paintEvent(QPaintEvent *event);
private:
	void drawBackground();
	void drawAxis();
	void drawData();
	void drawThreshold();
	Histogram m_histogram;
	QColor background;
	QColor threshold_brush_color;
	QColor threshold_pen_color;
	QColor histogram_pen_color;
	int m_low;
	int m_high;
};


#endif /* _HISTOGRAMCHART_H_ */
