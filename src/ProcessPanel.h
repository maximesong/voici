#ifndef _PROCESSPANEL_H_
#define _PROCESSPANEL_H_

#include <QWidget>

class QPushButton;
class QStackedWidget;
class QImage;

class ImageProcess;
class FilterPanel;
class TransformPanel;
class PointOperatorPanel;

class ProcessPanel : public QWidget {
	Q_OBJECT
public:
	ProcessPanel(const QImage &image, QWidget *parent = 0);
//	virtual ~ProcessPanel();
signals:
	void newProcess(ImageProcess *process);
public slots:
	void switchToFilterPanel();
	void switchToTransformPanel();
	void switchToPointOperatorPanel();
private:

	QWidget *buttonsWidget;
	QStackedWidget *stackedWidget;
	FilterPanel *filterPanel;
	TransformPanel *transformPanel;
	PointOperatorPanel *pointOperatorPanel;
};

#endif /* _PROCESSPANEL_H_ */
