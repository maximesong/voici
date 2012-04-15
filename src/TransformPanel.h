#ifndef _TRANSFORMPANEL_H_
#define _TRANSFORMPANEL_H_

#include <QWidget>

#include "Process.h"

class QPushButton;
class SliderPanel;
class DoubleSliderPanel;

class TransformPanel : public QWidget {
	Q_OBJECT
public:
	TransformPanel(int defaultImageWidth = 300, int defaultImageHeight = 300,
		       QWidget *parent = 0);
//	virtual ~TransformPanel();
	int getScaleWidth();
	int getScaleHeight();
	double getRotateAngle();
signals:
	void newProcess(SharedProcess process);
public slots:
	void sendBilinearScaleProcess();
	void sendNearestNeighbourScaleProcess();
	void sendNearestNeighbourRotateProcess();
private:
	SliderPanel *scaleWidthBox;
	SliderPanel *scaleHeightBox;
	DoubleSliderPanel *rotateAngleBox;
	QPushButton *nearestNeighbourScaleButton;
	QPushButton *bilinearScaleButton;
	QPushButton *nearestNeighbourRotateProcess;
};

#endif /* _TRANSFORMPANEL_H_ */
