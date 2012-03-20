#ifndef _HISTOGRAMPANEL_H_
#define _HISTOGRAMPANEL_H_

#include <QWidget>

class QCheckBox;

class ImageCore;
class HistogramChart;
class ThresholdPanel;

class HistogramPanel : public QWidget {
	Q_OBJECT
public:
	HistogramPanel(ImageCore *imageCore, QWidget *parent = 0);
signals:
	void thresholdChanged(int low, int high);
	void unsetThreshold();
public slots:
	void updateHistogramPanel(const ImageCore &imageCore);
	void enableThreshold(int state);
	void setThreshold(int low, int high);
private:
	HistogramChart *histogramChart;
	ThresholdPanel *thresholdPanel;
	QCheckBox *checkbox;
	bool isChangedByMyself;
	int m_low;
	int m_high;
};

#endif /* _HISTOGRAMPANEL_H_ */



