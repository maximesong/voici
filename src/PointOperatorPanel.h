#ifndef _POINTOPERATORPANEL_H_
#define _POINTOPERATORPANEL_H_

#include <QWidget>

class QDoubleSpinBox;
class QSpinBox;
class QPushButton;

class ImageProcess;

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
	void newProcess(ImageProcess *process);	
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
};

#endif /* _POINTOPERATORPANEL_H_ */