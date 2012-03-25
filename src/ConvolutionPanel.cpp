#include "ConvolutionPanel.h"

#include <QGridLayout>
#include <QPushButton>
#include <QVector>

#include "KernelTable.h"
#include "ProcessFactory.h"

ConvolutionPanel::ConvolutionPanel(QWidget *parent)
	: QWidget(parent)
{
	kernelTable = new KernelTable();
	robertsHButton = new QPushButton("RobertsH");
	robertsVButton = new QPushButton("RobertsV");
	prewittHButton = new QPushButton("PrewittH");
	prewittVButton = new QPushButton("PrewittV");
	sobelHButton = new QPushButton("SobelH");
	sobelVButton = new QPushButton("SobelV");
	applyButton = new QPushButton("Apply");


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
	layout->addWidget(robertsHButton, 5, 0, 1, 1);
	layout->addWidget(robertsVButton, 5, 1, 1, 1);
	layout->addWidget(prewittHButton, 6, 0, 1, 1);
	layout->addWidget(prewittVButton, 6, 1, 1, 1);
	layout->addWidget(sobelHButton, 7, 0, 1, 1);
	layout->addWidget(sobelVButton, 7, 1, 1, 1);
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
	ImageProcess *process = ProcessFactory::getConvolutionProcess(m, n, x, y, matrix);
	emit newProcess(process);
}
