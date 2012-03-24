#ifndef _CONVOLUTIONPANEL_H_
#define _CONVOLUTIONPANEL_H_

#include <QWidget>

class KernelTable;
class QPushButton;

class ConvolutionPanel : public QWidget {
	Q_OBJECT
public:
	ConvolutionPanel(QWidget *parent = 0);
signals:
		
public slots:
	
private:
	KernelTable *kernelTable;
	QPushButton *edgeButton;
	QPushButton *applyButton;
};

#endif /* _CONVOLUTIONPANEL_H_ */
