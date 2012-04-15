#ifndef _POINTOPERATORPANEL_H_
#define _POINTOPERATORPANEL_H_

#include <QWidget>

#include "Process.h"

class QDoubleSpinBox;
class QSpinBox;
class QPushButton;

class PointOperatorPanel : public QWidget {
	Q_OBJECT
public:
	PointOperatorPanel(QWidget *parent = 0);
//	virtual ~PointOperatorPanel();
	enum ProcessId {
		Linear,
		MidlevelNonlinear,
	};
signals:
	void newProcess(SharedProcess process);	
public slots:
	void sendPointLinearProcess();
	void sendMidlevelNonlinearProcess();
private:
	QDoubleSpinBox *kBox;
	QDoubleSpinBox *bBox;
	QDoubleSpinBox *cBox;
	QSpinBox *maxLevelBox;
	QPushButton *pointLinearButton;
	QPushButton *midlevelNonlinearButton;
	QPushButton *pointOperatorPanelButton;
};

#endif /* _POINTOPERATORPANEL_H_ */
