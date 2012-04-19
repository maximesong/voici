#include "ConvolutionPanel.h"

#include <QGridLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QIcon>
#include <QVector>

#include "KernelTable.h"
#include "ProcessFactory.h"
#include "VoiciMainWindow.h"

ConvolutionPanel::ConvolutionPanel(QWidget *parent)
	: QWidget(parent)
{
	kernelTable = new KernelTable();

	robertsHButton = new QPushButton(QIcon(":images/horizontal.png"), tr("RobertsH"));
	robertsVButton = new QPushButton(QIcon(":images/vertical.png"), tr("RobertsV"));
	QGroupBox *robertsGroup = new QGroupBox(tr("Roberts Operator"));
	QHBoxLayout *robertsLayout = new QHBoxLayout();
	robertsLayout->addWidget(robertsHButton);
	robertsLayout->addWidget(robertsVButton);
	robertsGroup->setLayout(robertsLayout);

	prewittHButton = new QPushButton(QIcon(":images/horizontal.png"), tr("PrewittH"));
	prewittVButton = new QPushButton(QIcon(":images/vertical.png"), tr("PrewittV"));
	QGroupBox *prewittGroup = new QGroupBox(tr("Prewitt Operator"));
	QHBoxLayout *prewittLayout = new QHBoxLayout();
	prewittLayout->addWidget(prewittHButton);
	prewittLayout->addWidget(prewittVButton);
	prewittGroup->setLayout(prewittLayout);

	sobelHButton = new QPushButton(QIcon(":images/horizontal.png"), tr("SobelH"));
	sobelVButton = new QPushButton(QIcon(":images/vertical.png"), tr("SobelV"));
	applyButton = new QPushButton(QIcon(":images/check.png"), tr("Apply"));
	QGroupBox *sobelGroup = new QGroupBox(tr("Sobel Operator"));
	QHBoxLayout *sobelLayout = new QHBoxLayout();
	sobelLayout->addWidget(sobelHButton);
	sobelLayout->addWidget(sobelVButton);
	sobelGroup->setLayout(sobelLayout);

	connect(robertsHButton, SIGNAL(clicked()), 
		this, SLOT(setRobertsH()));

	connect(robertsVButton, SIGNAL(clicked()), 
		this, SLOT(setRobertsV()));

	connect(prewittHButton, SIGNAL(clicked()), 
		this, SLOT(setPrewittH()));

	connect(prewittVButton, SIGNAL(clicked()), 
		this, SLOT(setPrewittV()));

	connect(sobelHButton, SIGNAL(clicked()), 
		this, SLOT(setSobelH()));

	connect(sobelVButton, SIGNAL(clicked()), 
		this, SLOT(setSobelV()));

	connect(applyButton, SIGNAL(clicked()), 
		this, SLOT(applyProcess()));


	QGridLayout *layout = new QGridLayout();
	layout->addWidget(kernelTable, 0, 0, 4, 6);
	layout->addWidget(robertsGroup, 5, 0, 1, 1);
	layout->addWidget(prewittGroup, 6, 0, 1, 1);
	layout->addWidget(sobelGroup, 7, 0, 1, 1);
	layout->addWidget(applyButton, 9, 0, 1, 1);
	
	setLayout(layout);
}

void ConvolutionPanel::setSobelH()
{
	double init_list[] = { -1, 0, 1,
			       -2, 0, 2,
			       -1, 0, 1 };

	setKernel(3, 3, 2, 2, init_list);
}

void ConvolutionPanel::setSobelV()
{
	double init_list[] = { -1, -2, -1,
			       0, 0, 0,
			       1, 2, 1 };

	setKernel(3, 3, 2, 2, init_list);
}

void ConvolutionPanel::setRobertsH()
{
	double init_list[] = { 1, 0,
			       0, -1 };

	setKernel(2, 2, 2, 2, init_list);
}

void ConvolutionPanel::setRobertsV()
{
	double init_list[] = { 0, 1,
			       -1, 0 };

	setKernel(2, 2, 2, 2, init_list);
}

void ConvolutionPanel::setPrewittH()
{
	double init_list[] = { -1, 0, 1,
			       -1, 0, 1,
			       -1, 0, 1 };

	setKernel(3, 3, 2, 2, init_list);
}

void ConvolutionPanel::setPrewittV()
{
	double init_list[] = { 1, 1, 1,
			       0, 0, 0,
			       -1, -1, -1 };

	setKernel(3, 3, 2, 2, init_list);
}

void ConvolutionPanel::setKernel(int m, int n, int x, int y, const double *init_list)
{
	QVector<double> matrix;
	for (int i = 0; i != m * n; ++i)
		matrix.append(init_list[i]);
	kernelTable->setKernel(m, n, x, y, matrix);
}

void ConvolutionPanel::applyProcess()
{
	QVector<double> matrix = kernelTable->getMatrix();
	int m = kernelTable->getRows();
	int n = kernelTable->getColumns();
	int x = kernelTable->getCenterRow();
	int y = kernelTable->getCenterColumn();
	SharedProcess process = 
		ProcessFactory::getConvolutionProcess(m, n, x, y, 
						      matrix,
						      mainWindow->getArea());
	emit newProcess(process);
}
