#include <QAction>
#include <QToolBar>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>

#include "VoiciMainWindow.h"
#include "PaintCanvas.h"

VoiciMainWindow::VoiciMainWindow()
{
	createActions();
	createToolBars();
	imageLabel = new PaintCanvas();
	this->setCentralWidget(imageLabel);

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
	imageLabel->loadImage(filename);
	imageLabel->update();
//	imageLabel->setPixmap(QPixmap::fromImage(image));
//	imageLabel->adjustSize();
}


VoiciMainWindow::~VoiciMainWindow()
{
	delete openAction;
	delete saveAction;
	delete fileToolBar;
	delete imageLabel;
}
