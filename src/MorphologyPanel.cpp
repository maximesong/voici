#include "MorphologyPanel.h"

#include <QGridLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QIcon>
#include <QVector>

#include "KernelTable.h"
#include "ProcessFactory.h"
#include "VoiciMainWindow.h"

MorphologyPanel::MorphologyPanel(QWidget *parent)
	: QWidget(parent)
{
	kernelTable = new KernelTable();

	dilationButton = new QPushButton(tr("Dilation"));
	erosionButton = new QPushButton(tr("Erosion"));
	QGroupBox *dilationErosionGroup = 
		new QGroupBox(tr("Dilation And Erosion"));
	QHBoxLayout *dilationErosionLayout = new QHBoxLayout();
	dilationErosionLayout->addWidget(dilationButton);
	dilationErosionLayout->addWidget(erosionButton);
	dilationErosionGroup->setLayout(dilationErosionLayout);

	openButton = new QPushButton(tr("Open"));
	closeButton = new QPushButton(tr("Close"));
	QGroupBox *openCloseGroup = 
		new QGroupBox(tr("Open And Close"));
	QHBoxLayout *openCloseLayout = new QHBoxLayout();
	openCloseLayout->addWidget(openButton);
	openCloseLayout->addWidget(closeButton);
	openCloseGroup->setLayout(openCloseLayout);

	connect(dilationButton, SIGNAL(clicked()), 
		this, SLOT(applyDilation()));

	connect(erosionButton, SIGNAL(clicked()), 
		this, SLOT(applyErosion()));

	connect(openButton, SIGNAL(clicked()), 
		this, SLOT(applyOpen()));

	connect(closeButton, SIGNAL(clicked()), 
		this, SLOT(applyClose()));


	QGridLayout *layout = new QGridLayout();
	layout->addWidget(kernelTable, 0, 0, 4, 6);
	layout->addWidget(dilationErosionGroup, 5, 0, 1, 1);
	layout->addWidget(openCloseGroup, 6, 0, 1, 1);
	
	setLayout(layout);
}


void MorphologyPanel::setKernel(int m, int n, int x, int y, const double *init_list)
{
	QVector<double> matrix;
	for (int i = 0; i != m * n; ++i)
		matrix.append(init_list[i]);
	kernelTable->setKernel(m, n, x, y, matrix);
}

void MorphologyPanel::applyDilation()
{
	QVector<double> double_matrix = kernelTable->getMatrix();
	QVector<int> matrix;
	for (int i = 0; i != double_matrix.size(); ++i) {
		matrix.push_back(double_matrix[i]);
	}
	int m = kernelTable->getRows();
	int n = kernelTable->getColumns();
	int x = kernelTable->getCenterRow();
	int y = kernelTable->getCenterColumn();
	SharedProcess process = 
		ProcessFactory::getDilationProcess(m, n, x, y, 
						      matrix,
						      mainWindow->getArea());
	emit newProcess(process);
}


void MorphologyPanel::applyErosion()
{
	QVector<double> double_matrix = kernelTable->getMatrix();
	QVector<int> matrix;
	for (int i = 0; i != double_matrix.size(); ++i) {
		matrix.push_back(double_matrix[i]);
	}
	int m = kernelTable->getRows();
	int n = kernelTable->getColumns();
	int x = kernelTable->getCenterRow();
	int y = kernelTable->getCenterColumn();
	SharedProcess process = 
		ProcessFactory::getErosionProcess(m, n, x, y, 
						      matrix,
						      mainWindow->getArea());
	emit newProcess(process);
}


void MorphologyPanel::applyOpen()
{
	QVector<double> double_matrix = kernelTable->getMatrix();
	QVector<int> matrix;
	for (int i = 0; i != double_matrix.size(); ++i) {
		matrix.push_back(double_matrix[i]);
	}
	int m = kernelTable->getRows();
	int n = kernelTable->getColumns();
	int x = kernelTable->getCenterRow();
	int y = kernelTable->getCenterColumn();
	SharedProcess process = 
		ProcessFactory::getOpenProcess(m, n, x, y, 
						      matrix,
						      mainWindow->getArea());
	emit newProcess(process);
}

void MorphologyPanel::applyClose()
{
	QVector<double> double_matrix = kernelTable->getMatrix();
	QVector<int> matrix;
	for (int i = 0; i != double_matrix.size(); ++i) {
		matrix.push_back(double_matrix[i]);
	}
	int m = kernelTable->getRows();
	int n = kernelTable->getColumns();
	int x = kernelTable->getCenterRow();
	int y = kernelTable->getCenterColumn();
	SharedProcess process = 
		ProcessFactory::getCloseProcess(m, n, x, y, 
						      matrix,
						      mainWindow->getArea());
	emit newProcess(process);
}
