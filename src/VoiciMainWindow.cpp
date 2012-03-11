#include <QAction>
#include <QToolBar>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>

#include "VoiciMainWindow.h"
#include "PaintCanvas.h"
#include "Histogram.h"

VoiciMainWindow::VoiciMainWindow()
{
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

	paintCanvas = new PaintCanvas(this);
	histogram = new Histogram(this);
	layout->addWidget(paintCanvas);
	
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
	paintCanvas->loadImage(filename);
	paintCanvas->update();
}


VoiciMainWindow::~VoiciMainWindow()
{
	delete openAction;
	delete saveAction;
	delete fileToolBar;
	delete imageLabel;
}
