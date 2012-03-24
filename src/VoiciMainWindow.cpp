#include "VoiciMainWindow.h"

#include <QAction>
#include <QToolBar>
#include <QGridLayout>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>

#include "PaintCanvas.h"
#include "ThresholdPanel.h"
#include "ImageCore.h"
#include "SliderPanel.h"
#include "HistogramPanel.h"
#include "GrayImageCore.h"
#include "KernelTable.h"
#include "ConvolutionPanel.h"

VoiciMainWindow::VoiciMainWindow()
{
	imageCore = new ImageCore();
	grayImageCore = new GrayImageCore();
	connect(imageCore, SIGNAL(imageChanged(const ImageCore&)),
  		grayImageCore, SLOT(setColorfulImage(const ImageCore&)));

	createActions();
	createToolBars();
	createCentralWidget();


	setWindowTitle(tr("Voici Image Processor"));
	resize(800, 600);
}


void VoiciMainWindow::createToolBars()
{
	fileToolBar = this->addToolBar(tr("File"));
	fileToolBar->addAction(openAction);
	fileToolBar->addAction(saveAction);
}


void VoiciMainWindow::createActions()
{
	openAction = new QAction("Open", this);
	connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

	saveAction = new QAction("Save", this);
	connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
}

void VoiciMainWindow::createCentralWidget()
{
	QWidget *centerWidget = new QWidget(this);

	displayPanel = new QTabWidget();
	controlPanel = new QTabWidget();


	QGridLayout *layout = new QGridLayout();
	layout->addWidget(displayPanel, 0, 0, 9, 6);
	layout->addWidget(controlPanel, 0, 6, 10, 4);
	centerWidget->setLayout(layout);
	this->setCentralWidget(centerWidget);
}

void VoiciMainWindow::open()
{
	QString fileName = QFileDialog::getOpenFileName(this,
							tr("Open Image"), 
							".",
							tr("all(*.png *.jpg)"));
	if (!fileName.isEmpty()) {
		loadFile(fileName);
		currentFileName = fileName;

		replaceTabWidget(displayPanel, &paintCanvas, new PaintCanvas(),
			fileName);
		connect(imageCore, SIGNAL(imageChanged(const ImageCore&)), 
			paintCanvas, SLOT(drawImage(const ImageCore&)));

		replaceTabWidget(displayPanel, &grayPaintCanvas, 
				 new PaintCanvas(), "Gray");
		connect(grayImageCore, SIGNAL(imageChanged(const ImageCore&)), 
			grayPaintCanvas, SLOT(drawImage(const ImageCore&)));

		displayPanel->addTab(paintCanvas, fileName);
		displayPanel->addTab(grayPaintCanvas, "Gray");
		paintCanvas->drawImage(*imageCore);
		grayPaintCanvas->drawImage(*grayImageCore);

		replaceTabWidget(controlPanel, &histogramPanel, 
				 new HistogramPanel(imageCore), "Histogram");

		connect(histogramPanel, SIGNAL(thresholdChanged(int, int)), 
			grayImageCore, SLOT(setThreshold(int,int)));
		connect(histogramPanel, SIGNAL(unsetThreshold()), 
			grayImageCore, SLOT(unsetThreshold()));

		replaceTabWidget(controlPanel, &convolutionPanel,
				 new ConvolutionPanel(), "Convolution");

	}
}

void VoiciMainWindow::save()
{
	/* TO BE IMPLEMENTED */
}


void VoiciMainWindow::loadFile(const QString &filename)
{
	imageCore->load(filename);
}


VoiciMainWindow::~VoiciMainWindow()
{
	delete imageCore;
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
