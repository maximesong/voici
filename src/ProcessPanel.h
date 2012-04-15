#ifndef _PROCESSPANEL_H_
#define _PROCESSPANEL_H_

#include <QWidget>

#include "Process.h"

class QPushButton;
class QStackedWidget;
class QImage;

class FilterPanel;
class TransformPanel;
class PointOperatorPanel;

class ProcessPanel : public QWidget {
	Q_OBJECT
public:
	ProcessPanel(const QImage &image, QWidget *parent = 0);
//	virtual ~ProcessPanel();
signals:
	void newProcess(SharedProcess process);
public slots:
	void switchToFilterPanel();
	void switchToTransformPanel();
	void switchToPointOperatorPanel();
private:
	void uncheckAllButton();
	QWidget *buttonsWidget;
	QStackedWidget *stackedWidget;
	FilterPanel *filterPanel;
	TransformPanel *transformPanel;
	PointOperatorPanel *pointOperatorPanel;
	QPushButton *filterPanelButton;
	QPushButton *transformPanelButton;
	QPushButton *pointOperatorPanelButton;
};

#endif /* _PROCESSPANEL_H_ */
