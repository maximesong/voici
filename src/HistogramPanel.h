#ifndef _HISTOGRAMPANEL_H_
#define _HISTOGRAMPANEL_H_

#include <QWidget>

class ImageCore;
class HistogramChart;
class ThresholdPanel;

class HistogramPanel : public QWidget {
	Q_OBJECT
public:
	HistogramPanel(ImageCore *imageCore, QWidget *parent = 0);
signals:
	void imageChanged();
public slots:
	void updateHistogramPanel(const ImageCore &imageCore);
private:
	HistogramChart *histogramChart;
	ThresholdPanel *thresholdPanel;
	bool isChangedByMyself;
};

#endif /* _HISTOGRAMPANEL_H_ */



