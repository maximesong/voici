#ifndef _CONVOLUTIONPANEL_H_
#define _CONVOLUTIONPANEL_H_

#include <QWidget>

class QPushButton;

class KernelTable;
class ImageProcess;

class ConvolutionPanel : public QWidget {
	Q_OBJECT
public:
	ConvolutionPanel(QWidget *parent = 0);
signals:
	void newProcess(ImageProcess *process);

public slots:
	void setSobelH();
	void setSobelV();
	void setRobertsH();
	void setRobertsV();
	void setPrewittH();
	void setPrewittV();
	void applyProcess();
private:
	void setKernel(int m, int n, int x, int y, const double *init_list);
	KernelTable *kernelTable;
	QPushButton *robertsHButton;
	QPushButton *robertsVButton;
	QPushButton *prewittHButton;
	QPushButton *prewittVButton;
	QPushButton *sobelHButton;
	QPushButton *sobelVButton;
	QPushButton *applyButton;
};

#endif /* _CONVOLUTIONPANEL_H_ */
