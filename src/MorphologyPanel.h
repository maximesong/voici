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
	void applyGrayDilation();
	void applyGrayErosion();
	void applyGrayOpen();
	void applyGrayClose();
	void applySkeleton();
	void applyDistance();
	void applyEdge();
	void setCrossKernel();
	void setSquareKernel();
	void setEmptyKernel();

private:
	void setKernel(int m, int n, int x, int y, const double *init_list);
	KernelTable *kernelTable;
	QPushButton *dilationButton;
	QPushButton *erosionButton;
	QPushButton *openButton;
	QPushButton *closeButton;
	QPushButton *grayDilationButton;
	QPushButton *grayErosionButton;
	QPushButton *grayOpenButton;
	QPushButton *grayCloseButton;
	QPushButton *skeletonButton;
	QPushButton *distanceButton;
	QPushButton *edgeButton;
};

#endif /* _MORPHOLOGYPANEL_H_ */
