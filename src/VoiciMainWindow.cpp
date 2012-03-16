#include "VoiciMainWindow.h"

#include <iostream>

#include <QAction>
#include <QToolBar>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>

#include "PaintCanvas.h"
#include "HistogramChart.h"
#include "ThresholdPanel.h"
#include "ImageCore.h"
#include "SliderPanel.h"

VoiciMainWindow::VoiciMainWindow()
{
	imageCore = new ImageCore();

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
	centerWidget = new QWidget(this);
	QHBoxLayout *layout = new QHBoxLayout();


	paintCanvas = new PaintCanvas();
	connect(imageCore, SIGNAL(imageChanged(const ImageCore&)), 
		paintCanvas, SLOT(drawImage(const ImageCore&)));

	histogramChart = new HistogramChart();
	connect(imageCore, SIGNAL(imageChanged(const ImageCore&)), 
		histogramChart, SLOT(drawChart(const ImageCore&)));
	
//	SliderPanel *sliderPanel = new SliderPanel("Max");
//	layout->addWidget(sliderPanel);

	ThresholdPanel *thresholdPanel = new ThresholdPanel();
	
	layout->addWidget(paintCanvas);
	layout->addWidget(histogramChart);
	layout->addWidget(thresholdPanel);
//	std::cout << thresholdPanel->height() << " " << thresholdPanel->width()
//		  << std::endl;
	centerWidget->setLayout(layout);
	this->setCentralWidget(centerWidget);
}

void VoiciMainWindow::open()
{
	QString fileName = QFileDialog::getOpenFileName(this,
							tr("Open Image"), 
							".",
							tr("all(*.png)"));
	if (!fileName.isEmpty()) {
		loadFile(fileName);
		currentFileName = fileName;
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
