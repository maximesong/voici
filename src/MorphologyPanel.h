#ifndef _MORPHOLOGYPANEL_H_
#define _MORPHOLOGYPANEL_H_

#include <QWidget>

#include "Process.h"

class QPushButton;

class KernelTable;

class MorphologyPanel : public QWidget {
	Q_OBJECT
public:
	MorphologyPanel(QWidget *parent = 0);
signals:
	void newProcess(SharedProcess process);

public slots:
	void applyDilation();
	void applyErosion();
	void applyOpen();
	void applyClose();
private:
	void setKernel(int m, int n, int x, int y, const double *init_list);
	KernelTable *kernelTable;
	QPushButton *dilationButton;
	QPushButton *erosionButton;
	QPushButton *openButton;
	QPushButton *closeButton;
};

#endif /* _MORPHOLOGYPANEL_H_ */
