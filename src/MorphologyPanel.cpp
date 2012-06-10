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
	setCrossKernel();

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


	grayDilationButton = new QPushButton(tr("GrayDilation"));
	grayErosionButton = new QPushButton(tr("GrayErosion"));
	QGroupBox *grayDilationErosionGroup = 
		new QGroupBox(tr("GrayDilation And GrayErosion"));
	QHBoxLayout *grayDilationErosionLayout = new QHBoxLayout();
	grayDilationErosionLayout->addWidget(grayDilationButton);
	grayDilationErosionLayout->addWidget(grayErosionButton);
	grayDilationErosionGroup->setLayout(grayDilationErosionLayout);

	grayOpenButton = new QPushButton(tr("GrayOpen"));
	grayCloseButton = new QPushButton(tr("GrayClose"));
	QGroupBox *grayOpenCloseGroup = 
		new QGroupBox(tr("GrayOpen And GrayClose"));
	QHBoxLayout *grayOpenCloseLayout = new QHBoxLayout();
	grayOpenCloseLayout->addWidget(grayOpenButton);
	grayOpenCloseLayout->addWidget(grayCloseButton);
	grayOpenCloseGroup->setLayout(grayOpenCloseLayout);

	connect(grayDilationButton, SIGNAL(clicked()), 
		this, SLOT(applyGrayDilation()));

	connect(grayErosionButton, SIGNAL(clicked()), 
		this, SLOT(applyGrayErosion()));

	connect(grayOpenButton, SIGNAL(clicked()), 
		this, SLOT(applyGrayOpen()));

	connect(grayCloseButton, SIGNAL(clicked()), 
		this, SLOT(applyGrayClose()));

	skeletonButton = new QPushButton(tr("Skeleton"));
	restoreButton = new QPushButton(tr("Restoration(not work)"));
	QGroupBox *skeletonGroup = 
		new QGroupBox(tr("Skeleton"));
	QHBoxLayout *skeletonLayout = new QHBoxLayout();
	skeletonLayout->addWidget(skeletonButton);
	skeletonLayout->addWidget(restoreButton);
	skeletonGroup->setLayout(skeletonLayout);

	connect(skeletonButton, SIGNAL(clicked()), 
		this, SLOT(applySkeleton()));
	connect(restoreButton, SIGNAL(clicked()), 
		this, SLOT(applyRestore()));

	reconstructButton = new QPushButton(tr("Reconstruct"));
	grayReconstructButton = new QPushButton(tr("GrayReconstruct"));
	QGroupBox *reconstructGroup = 
		new QGroupBox(tr("Reconstruct"));
	QHBoxLayout *reconstructLayout = new QHBoxLayout();
	reconstructLayout->addWidget(reconstructButton);
	reconstructLayout->addWidget(grayReconstructButton);
	reconstructGroup->setLayout(reconstructLayout);

	connect(reconstructButton, SIGNAL(clicked()), 
		this, SLOT(applyReconstruct()));
	connect(grayReconstructButton, SIGNAL(clicked()), 
		this, SLOT(applyGrayReconstruct()));

	edgeButton = new QPushButton(tr("Edge"));
	gradientButton = new QPushButton(tr("Gradient"));
	QGroupBox *moreGroup = 
		new QGroupBox(tr("More"));
	QHBoxLayout *moreLayout = new QHBoxLayout();
	moreLayout->addWidget(edgeButton);
	moreLayout->addWidget(gradientButton);
	moreGroup->setLayout(moreLayout);

	connect(edgeButton, SIGNAL(clicked()), 
		this, SLOT(applyEdge()));
	connect(gradientButton, SIGNAL(clicked()), 
		this, SLOT(applyGradient()));

	distanceButton = new QPushButton(tr("Distance"));
	QGroupBox *distanceGroup = 
		new QGroupBox(tr("Distance"));
	QHBoxLayout *distanceLayout = new QHBoxLayout();
	distanceLayout->addWidget(distanceButton);
	distanceGroup->setLayout(distanceLayout);

	connect(distanceButton, SIGNAL(clicked()), 
		this, SLOT(applyDistance()));


	QGridLayout *layout = new QGridLayout();
	layout->addWidget(kernelTable, 0, 0, 4, 6);
	layout->addWidget(dilationErosionGroup, 5, 0, 1, 1);
	layout->addWidget(openCloseGroup, 6, 0, 1, 1);
	layout->addWidget(grayDilationErosionGroup, 7, 0, 1, 1);
	layout->addWidget(grayOpenCloseGroup, 8, 0, 1, 1);
	layout->addWidget(skeletonGroup, 5, 1, 1, 1);
	layout->addWidget(distanceGroup, 6, 1, 1, 1);
	layout->addWidget(reconstructGroup, 7, 1, 1, 1);
	layout->addWidget(moreGroup, 8, 1, 1, 1);
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

void MorphologyPanel::applyGrayDilation()
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
		ProcessFactory::getGrayDilationProcess(m, n, x, y, 
						       matrix,
						       mainWindow->getArea());
	emit newProcess(process);
}


void MorphologyPanel::applyGrayErosion()
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
		ProcessFactory::getGrayErosionProcess(m, n, x, y, 
						      matrix,
						      mainWindow->getArea());
	emit newProcess(process);
}


void MorphologyPanel::applyGrayOpen()
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
		ProcessFactory::getGrayOpenProcess(m, n, x, y, 
						   matrix,
						   mainWindow->getArea());
	emit newProcess(process);
}

void MorphologyPanel::applyGrayClose()
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
		ProcessFactory::getGrayCloseProcess(m, n, x, y, 
						    matrix,
						    mainWindow->getArea());
	emit newProcess(process);
}


void MorphologyPanel::applySkeleton()
{
	setCrossKernel();
	SharedProcess process = ProcessFactory::getMorphoSkeletonProcess();
	emit newProcess(process);
}

void MorphologyPanel::applyDistance()
{
	setSquareKernel();
	SharedProcess process = ProcessFactory::getMorphoDistanceProcess();
	emit newProcess(process);
}

void MorphologyPanel::setCrossKernel()
{
	double kernel[9] =  { 0, 255, 0,
			      255, 255, 255,
			      0, 255, 0 };
	setKernel(3, 3, 2, 2, kernel);
}

void MorphologyPanel::setSquareKernel()
{
	double kernel[9] =  { 255, 255, 255,
			      255, 255, 255,
			      255, 255, 255 };
	setKernel(3, 3, 2, 2, kernel);
}

void MorphologyPanel::setEmptyKernel()
{
	double kernel[9] =  { 0, 0, 0,
			      0, 0, 0,
			      0, 0, 0 };
	setKernel(3, 3, 2, 2, kernel);
}

void MorphologyPanel::applyEdge()
{
	setSquareKernel();
	SharedProcess process = 
		ProcessFactory::getMorphoHelperProcess(MORPHO_EDGE);
	emit newProcess(process);
}

void MorphologyPanel::applyGradient()
{
	setSquareKernel();
	SharedProcess process = 
		ProcessFactory::getMorphoHelperProcess(MORPHO_GRADIENT);
	emit newProcess(process);
}

void MorphologyPanel::applyRestore()
{
	setCrossKernel();
	SharedProcess process = 
		ProcessFactory::getMorphoHelperProcess(MORPHO_RESTORATION);
	emit newProcess(process);
}


void MorphologyPanel::applyReconstruct()
{
	setSquareKernel();
	SharedProcess process = 
		ProcessFactory::getMorphoHelperProcess(MORPHO_RECONSTRUCT);
	emit newProcess(process);
}

void MorphologyPanel::applyGrayReconstruct()
{
	setSquareKernel();
	SharedProcess process = 
		ProcessFactory::getMorphoHelperProcess(MORPHO_GRAY_RECONSTRUCT);
	emit newProcess(process);
}
