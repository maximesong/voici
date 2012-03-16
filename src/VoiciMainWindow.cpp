#include "VoiciMainWindow.h"

#include <iostream>

#include <QAction>
#include <QToolBar>
#include <QGridLayout>
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
							tr("all(*.png)"));
	if (!fileName.isEmpty()) {
		loadFile(fileName);
		currentFileName = fileName;

		int paintCanvasIndex = displayPanel->indexOf(paintCanvas);
		if (paintCanvasIndex != -1) {
			displayPanel->removeTab(paintCanvasIndex);
			delete paintCanvas;
		}
		paintCanvas = new PaintCanvas();

		connect(imageCore, SIGNAL(imageChanged(const ImageCore&)), 
			paintCanvas, SLOT(drawImage(const ImageCore&)));
		
		displayPanel->addTab(paintCanvas, fileName);
		paintCanvas->drawImage(*imageCore);
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



