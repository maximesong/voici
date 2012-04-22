#ifndef _PROCESSPANEL_H_
#define _PROCESSPANEL_H_

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QImage>

#include "Process.h"
#include "ActionPanel.h"

class ActionButton;
class FilterPanel;
class TransformPanel;
class PointOperatorPanel;
class ContrastPanel;
class FiltersPanel;

class ProcessPanel : public ActionPanel {
	Q_OBJECT
public:
	enum Action { Filter, Filters, Transform,
		      PointOperator, Contrast };
	ProcessPanel(const QImage &image, QWidget *parent = 0);
signals:
	void newProcess(SharedProcess process);
public slots:
	virtual void processButtonClicked(int action);
protected:
	void switchToPanel(int action);
	virtual void doCreation();
	virtual void doConnections();
	virtual void doLayout();
	virtual void addPanel(const QString &text, int action, QWidget *panel);
private:
	void uncheckAllButton();
	QWidget *buttonsWidget;
	QStackedWidget *stackedWidget;

	FilterPanel *filterPanel;
	TransformPanel *transformPanel;
	PointOperatorPanel *pointOperatorPanel;
	ContrastPanel *contrastPanel;
	FiltersPanel *filtersPanel;

	QVector<QWidget*> m_panels;
};

#endif /* _PROCESSPANEL_H_ */
