#ifndef _TRANSFORMPANEL_H_
#define _TRANSFORMPANEL_H_

#include <QWidget>

class QPushButton;
class QSpinBox;
class QDoubleSpinBox;

class ImageProcess;

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
	void newProcess(ImageProcess *process);
public slots:
	void sendBilinearScaleProcess();
	void sendNearestNeighbourScaleProcess();
	void sendNearestNeighbourRotateProcess();
private:
	QSpinBox *scaleWidthBox;
	QSpinBox *scaleHeightBox;
	QDoubleSpinBox *rotateAngleBox;
	QPushButton *nearestNeighbourScaleButton;
	QPushButton *bilinearScaleButton;
	QPushButton *nearestNeighbourRotateProcess;
};

#endif /* _TRANSFORMPANEL_H_ */
