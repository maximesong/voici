#ifndef _PROCESSPANEL_H_
#define _PROCESSPANEL_H_

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QImage>

#include "Process.h"

class FilterPanel;
class TransformPanel;
class PointOperatorPanel;
class ContrastPanel;
class FiltersPanel;

class ProcessPanel : public QWidget {
	Q_OBJECT
public:
	ProcessPanel(const QImage &image, QWidget *parent = 0);
//	virtual ~ProcessPanel();
signals:
	void newProcess(SharedProcess process);
public slots:
	void switchToFilterPanel();
	void switchToFiltersPanel();
	void switchToTransformPanel();
	void switchToPointOperatorPanel();
	void switchToContrastPanel();
private:
	void uncheckAllButton();
	QWidget *buttonsWidget;
	QStackedWidget *stackedWidget;

	FilterPanel *filterPanel;
	TransformPanel *transformPanel;
	PointOperatorPanel *pointOperatorPanel;
	ContrastPanel *contrastPanel;
	FiltersPanel *filtersPanel;

	QPushButton *filterPanelButton;
	QPushButton *transformPanelButton;
	QPushButton *pointOperatorPanelButton;
	QPushButton *contrastPanelButton;
	QPushButton *filtersPanelButton;
};

#endif /* _PROCESSPANEL_H_ */
