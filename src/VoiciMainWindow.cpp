#include "VoiciMainWindow.h"

#include <iostream>
using namespace std;

#include <QAction>
#include <QIcon>
#include <QToolBar>
#include <QGridLayout>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QApplication>

#include "PaintCanvas.h"
#include "ThresholdPanel.h"
#include "SliderPanel.h"
#include "HistogramPanel.h"
#include "KernelTable.h"
#include "ConvolutionPanel.h"
#include "Exceptions.h"
#include "AlgebraicProcessPanel.h"
#include "ProcessPanel.h"

VoiciMainWindow::VoiciMainWindow()
{
	imageFamily = new ImageFamily();
	grayImageFamily = new ImageFamily();
	currentImageFamily = imageFamily;

	createActions();
	createToolBars();
	createCentralWidget();


	setWindowTitle(tr("Voici Image Processor"));
	QRect rect = QApplication::desktop()->availableGeometry();
	resize(rect.width(), rect.height());
}


void VoiciMainWindow::createToolBars()
{
	fileToolBar = this->addToolBar(tr("File"));
	fileToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	fileToolBar->addAction(openAction);
	fileToolBar->addAction(saveAction);
}


void VoiciMainWindow::createActions()
{
	openAction = new QAction(QIcon(":/images/open.png"), tr("&Open"), this);
	connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

	saveAction = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
	connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
}

void VoiciMainWindow::createCentralWidget()
{
	QWidget *centerWidget = new QWidget(this);

	displayPanel = new QTabWidget();
	connect(displayPanel, SIGNAL(currentChanged(int)), 
		this, SLOT(paintCanvasChanged()));

	controlPanel = new QTabWidget();


	QGridLayout *layout = new QGridLayout();
	layout->addWidget(displayPanel, 0, 0, 9, 6);
	layout->addWidget(controlPanel, 0, 6, 10, 4);
	centerWidget->setLayout(layout);
	this->setCentralWidget(centerWidget);
}

void VoiciMainWindow::open()
{
	QString filename = QFileDialog::getOpenFileName(this,
							tr("Open Image"), 
							".",
							tr("all(*.png *.jpg)"));
	loadFile(filename);
}

void VoiciMainWindow::save()
{
	QString filename = QFileDialog::getSaveFileName(this,
							tr("Save Image"), 
							".",
							tr("all(*.png *.jpg)"));
	if (filename == "")
		return;

	saveFile(filename);
}


void VoiciMainWindow::loadFile(const QString &filename)
{
	if (filename.isEmpty())
		return;

	imageFamily->loadOriginImage(filename);
	grayImageFamily->loadOriginImage(filename);

	currentFileName = filename;
	QImage image = imageFamily->getCurrentImage();

	replaceTabWidget(displayPanel, &paintCanvas, new PaintCanvas(),
			 filename);
	connect(imageFamily, SIGNAL(imageChanged(const ImageFamily&)), 
		paintCanvas, SLOT(drawImage(const ImageFamily&)));

	displayPanel->addTab(paintCanvas, filename);

	replaceTabWidget(displayPanel, &grayPaintCanvas, 
			 new PaintCanvas(), tr("Gray"));
	connect(grayImageFamily, SIGNAL(imageChanged(const ImageFamily&)), 
		grayPaintCanvas, SLOT(drawImage(const ImageFamily&)));

	paintCanvas->drawImage(*imageFamily);
	grayPaintCanvas->drawImage(*grayImageFamily);

	/* Add Process Panel */
	replaceTabWidget(controlPanel, &processPanel,
			 new ProcessPanel(image), tr("Process Panel"));

	connect(processPanel, SIGNAL(newProcess(SharedProcess)), 
		this, SLOT(addProcess(SharedProcess)));

	/* Add Histogram Panel */
	replaceTabWidget(controlPanel, &histogramPanel, 
			 new HistogramPanel(imageFamily), tr("Histogram"));

	connect(histogramPanel, SIGNAL(thresholdChanged(int, int)), 
		grayImageFamily, SLOT(setThreshold(int,int)));
	connect(histogramPanel, SIGNAL(unsetThreshold()), 
		grayImageFamily, SLOT(unsetThreshold()));

	/* Add Convolution Panel */
	replaceTabWidget(controlPanel, &convolutionPanel,
			 new ConvolutionPanel(), tr("Convolution"));

	connect(convolutionPanel, SIGNAL(newProcess(SharedProcess)), 
		grayImageFamily, SLOT(pushImageProcess(SharedProcess)));

	/* Add Alegbraic Process Panel */
	replaceTabWidget(controlPanel, &algebraicProcessPanel,
			 new AlgebraicProcessPanel(), tr("Alebraic Operations"));

	connect(algebraicProcessPanel, SIGNAL(newProcess(SharedProcess)), 
		this, SLOT(addProcess(SharedProcess)));


}

void VoiciMainWindow::saveFile(const QString &filename)
{
	QImage image = grayImageFamily->getCurrentImage();
	image.save(filename);
}

VoiciMainWindow::~VoiciMainWindow()
{
	delete imageFamily;
}


template <class T, class U>
void VoiciMainWindow::replaceTabWidget(QTabWidget *tabWidget, T **oldWidget, 
				       U *newWidget, const QString &label)
{
	int widgetIndex = tabWidget->indexOf(*oldWidget);
	if (widgetIndex != -1) {
		tabWidget->removeTab(widgetIndex);
		delete *oldWidget;
	}
	*oldWidget = newWidget;
	tabWidget->addTab(newWidget, label);
}

void VoiciMainWindow::addProcess(SharedProcess process)
{
	if (currentImageFamily == imageFamily) {
		if (process->canApplyToRgb()) {
			currentImageFamily->pushImageProcess(process);
			return;
		} else if (process->canApplyToGray()) {
			int result = 
				QMessageBox::question(this,
						      tr("Apply to gray image?"), 
						      tr("This process can not be applied to Rgb image. Would you like it be applied to gray image?"),
						      QMessageBox::Yes | QMessageBox::No,
						      QMessageBox::Yes);
			switch (result) {
			case QMessageBox::Yes:
				currentImageFamily = grayImageFamily;
				displayPanel->setCurrentWidget(grayPaintCanvas);
				currentImageFamily->pushImageProcess(process);
				return;
			case QMessageBox::No:
				return;
			}
		}
	} else {
		if (process->canApplyToGray()) {
			currentImageFamily->pushImageProcess(process);
			return;
		} else if (process->canApplyToRgb()) {
			int result = 
				QMessageBox::question(this,
						      tr("Apply to rgb image?"), 
						      tr("This process can not be applied to gray image. Would you like it be applied to rgb image?"),
						      QMessageBox::Yes | QMessageBox::No,
						      QMessageBox::Yes);
			switch (result) {
			case QMessageBox::Yes:
				currentImageFamily = imageFamily;
				displayPanel->setCurrentWidget(paintCanvas);
				currentImageFamily->pushImageProcess(process);
				return;
			case QMessageBox::No:
				return;
			}
		}
	}
	

}

void VoiciMainWindow::paintCanvasChanged()
{
	if (displayPanel->currentWidget() == grayPaintCanvas)
		currentImageFamily = grayImageFamily;
	else if (displayPanel->currentWidget() == paintCanvas)
		currentImageFamily = imageFamily;
}
