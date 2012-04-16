#ifndef _CONTRASTPANEL_H_
#define _CONTRASTPANEL_H_

#include <QWidget>
#include <QPushButton>

#include "Process.h"

class ContrastPanel : public QWidget {
	Q_OBJECT
public:
	ContrastPanel(QWidget *parent = 0);
//	virtual ~ContrastPanel();
signals:
	void newProcess(SharedProcess process);
public slots:
	void sendHistogramEqualizationProcess();
private:
	QPushButton *histogramEqualizationButton;
};

#endif /* _CONTRASTPANEL_H_ */
