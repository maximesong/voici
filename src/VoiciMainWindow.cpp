#include "VoiciMainWindow.h"

#include <QAction>
#include <QIcon>
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
#include "Exceptions.h"
#include "AlgebraicProcessPanel.h"
#include "ProcessPanel.h"

VoiciMainWindow::VoiciMainWindow()
{
	imageCore = new ImageCore();
	grayImageCore = new GrayImageCore();
	currentImageCore = grayImageCore;

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

	imageCore->load(filename);
	currentFileName = filename;

	replaceTabWidget(displayPanel, &paintCanvas, new PaintCanvas(),
			 filename);
	connect(imageCore, SIGNAL(imageChanged(const ImageCore&)), 
		paintCanvas, SLOT(drawImage(const ImageCore&)));

	displayPanel->addTab(paintCanvas, filename);

	replaceTabWidget(displayPanel, &grayPaintCanvas, 
			 new PaintCanvas(), tr("Gray"));
	connect(grayImageCore, SIGNAL(imageChanged(const ImageCore&)), 
		grayPaintCanvas, SLOT(drawImage(const ImageCore&)));

	paintCanvas->drawImage(*imageCore);
	grayPaintCanvas->drawImage(*grayImageCore);

	/* Add Histogram Panel */
	replaceTabWidget(controlPanel, &histogramPanel, 
			 new HistogramPanel(imageCore), tr("Histogram"));

	connect(histogramPanel, SIGNAL(thresholdChanged(int, int)), 
		grayImageCore, SLOT(setThreshold(int,int)));
	connect(histogramPanel, SIGNAL(unsetThreshold()), 
		grayImageCore, SLOT(unsetThreshold()));

	/* Add Convolution Panel */
	replaceTabWidget(controlPanel, &convolutionPanel,
			 new ConvolutionPanel(), tr("Convolution"));

	connect(convolutionPanel, SIGNAL(newProcess(ImageProcess *)), 
		grayImageCore, SLOT(pushImageProcess(ImageProcess *)));

	/* Add Alegbraic Process Panel */
	replaceTabWidget(controlPanel, &algebraicProcessPanel,
			 new AlgebraicProcessPanel(), tr("Alebraic Operations"));

	connect(algebraicProcessPanel, SIGNAL(newProcess(ImageProcess *)), 
		this, SLOT(addProcess(ImageProcess *)));

	/* Add Filter Panel */
	replaceTabWidget(controlPanel, &processPanel,
			 new ProcessPanel(), tr("Process Panel"));

	connect(processPanel, SIGNAL(newProcess(ImageProcess *)), 
		this, SLOT(addProcess(ImageProcess *)));
}

void VoiciMainWindow::saveFile(const QString &filename)
{
	QImage image = grayImageCore->getCurrentImage();
	image.save(filename);
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

void VoiciMainWindow::addProcess(ImageProcess *process)
{
	currentImageCore->pushImageProcess(process);
}
