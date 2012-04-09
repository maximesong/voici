#ifndef _TRANSFORMPANEL_H_
#define _TRANSFORMPANEL_H_

#include <QWidget>

class QPushButton;
class QSpinBox;

class ImageProcess;

class TransformPanel : public QWidget {
	Q_OBJECT
public:
	TransformPanel(int defaultImageWidth = 300, int defaultImageHeight = 300,
		       QWidget *parent = 0);
//	virtual ~TransformPanel();
	int getScaleWidth();
	int getScaleHeight();
signals:
	void newProcess(ImageProcess *process);
public slots:
	void sendBilinearScaleProcess();
	void sendNearestNeighbourScaleProcess();
private:
	QSpinBox *scaleWidthBox;
	QSpinBox *scaleHeightBox;
	QPushButton *nearestNeighbourScaleButton;
	QPushButton *bilinearScaleButton;
};

#endif /* _TRANSFORMPANEL_H_ */
