#include "VoiciMainWindow.h"

#include <iostream>
using namespace std;

#include <QAction>
#include <QIcon>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QApplication>
#include <QMenu>

#include "PaintCanvas.h"
#include "ThresholdPanel.h"
#include "SliderPanel.h"
#include "HistogramPanel.h"
#include "KernelTable.h"
#include "ConvolutionPanel.h"
#include "Exceptions.h"
#include "AlgebraicProcessPanel.h"
#include "ProcessPanel.h"
#include "ProcessFactory.h"
#include "IteratorArea.h"
#include "PaintOperator.h"

VoiciMainWindow::VoiciMainWindow()
{
	imageFamily = new ImageFamily(QImage(), tr("Colorful"));
	grayImageFamily = new ImageFamily(QImage(), tr("Gray"));
	currentImageFamily = imageFamily;
	paintOperator = new PaintOperator();
	connect(paintOperator, SIGNAL(areaChanged(IteratorArea*)), 
		this, SLOT(setIteratorArea(IteratorArea*)));


	createActions();
	createToolBars();
	createCentralWidget();

	connect(imageFamily, SIGNAL(undoAndRedoChanged(bool, bool)), 
		this, SLOT(setCanUndoAndRedo(bool, bool)));

	connect(grayImageFamily, SIGNAL(undoAndRedoChanged(bool, bool)), 
		this, SLOT(setCanUndoAndRedo(bool, bool)));

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
	fileToolBar->addAction(undoAction);
	fileToolBar->addAction(redoAction);
	fileToolBar->addAction(rectAction);
	fileToolBar->addAction(circleAction);
	setCanUndoAndRedo(0, 0);
}


void VoiciMainWindow::createActions()
{
	openAction = new QAction(QIcon(":/images/open.png"), tr("&Open"), this);
	connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

	saveAction = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
	connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

	undoAction = new QAction(QIcon(":images/undo.png"), tr("&Undo"), this);
	connect(undoAction, SIGNAL(triggered()), this, SLOT(undo()));

	redoAction = new QAction(QIcon(":images/redo.png"), tr("&Redo"), this);
	connect(redoAction, SIGNAL(triggered()), this, SLOT(redo()));

	rectAction = new QAction(QIcon(":images/rect_select.png"),
				 tr("Rectangle"), this);
	connect(rectAction, SIGNAL(triggered()), 
		this, SLOT(selectRectangle()));

	circleAction = new QAction(QIcon(":images/circle_select.png"),
				   tr("Circle"), this);
	connect(circleAction, SIGNAL(triggered()), 
		this, SLOT(selectCircle()));
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
							tr(acceptImageLabel));
	loadFile(filename);
}

void VoiciMainWindow::save()
{
	QFileDialog dialog(this, tr("Save Image"), ".", tr(acceptImageLabel));
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	if (!dialog.exec()) {
		return;
	}
	QString filename = dialog.selectedFiles()[0];
	QString filter = dialog.selectedNameFilter();
	int start = filter.lastIndexOf(".");
	int end = filter.lastIndexOf(")");
	QString suffix = "";
	for (int i = start; i != end; ++ i) {
		suffix.append(filter[i]);
	}
	if (!filename.endsWith(suffix)) {
		filename += suffix;
	}

	cout << suffix.toStdString() << endl;
	saveFile(filename);
}

void VoiciMainWindow::undo()
{
	currentImageFamily->popDynamicImageProcesser();
}

void VoiciMainWindow::redo()
{
	currentImageFamily->pushDynamicImageProcesser();
}

void VoiciMainWindow::loadFile(const QString &filename)
{
	if (filename.isEmpty())
		return;

	imageFamily->loadOriginImage(filename);
	grayImageFamily->loadOriginImage(filename);
	SharedProcess graying_process = ProcessFactory::getStandardGrayProcess();
	graying_process->applyToImageFamily(grayImageFamily);

	currentFileName = filename;
	QImage image = imageFamily->getCurrentImage();

	replaceTabWidget(displayPanel, &paintCanvas, new PaintCanvas(),
			 filename);
	currentPaintCanvas = paintCanvas;

	connect(imageFamily, SIGNAL(currentImageChanged(const ImageFamily&)), 
		paintCanvas, SLOT(drawImage(const ImageFamily&)));

	displayPanel->addTab(paintCanvas, filename);

	replaceTabWidget(displayPanel, &grayPaintCanvas, 
			 new PaintCanvas(), tr("Gray"));
	connect(grayImageFamily, SIGNAL(currentImageChanged(const ImageFamily&)), 
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

	connect(histogramPanel, SIGNAL(newProcess(SharedProcess)), 
		this, SLOT(addProcess(SharedProcess)));

	/* Add Convolution Panel */
	replaceTabWidget(controlPanel, &convolutionPanel,
			 new ConvolutionPanel(), tr("Convolution"));

	connect(convolutionPanel, SIGNAL(newProcess(SharedProcess)), 
		this, SLOT(addProcess(SharedProcess)));

	/* Add Alegbraic Process Panel */
	replaceTabWidget(controlPanel, &algebraicProcessPanel,
			 new AlgebraicProcessPanel(), tr("Alebraic Operations"));

	connect(algebraicProcessPanel, SIGNAL(newProcess(SharedProcess)), 
		this, SLOT(addProcess(SharedProcess)));

	setCanUndoAndRedo(0, 0);

	connect(paintCanvas, SIGNAL(mousePressed(QMouseEvent*)), 
		paintOperator, SLOT(mousePressed(QMouseEvent*)));

	connect(paintCanvas, SIGNAL(mouseMoved(QMouseEvent*)), 
		paintOperator, SLOT(mouseMoved(QMouseEvent*)));

	connect(paintCanvas, SIGNAL(mouseReleased(QMouseEvent*)), 
		paintOperator, SLOT(mouseReleased(QMouseEvent*)));

	connect(grayPaintCanvas, SIGNAL(mousePressed(QMouseEvent*)), 
		paintOperator, SLOT(mousePressed(QMouseEvent*)));

	connect(grayPaintCanvas, SIGNAL(mouseMoved(QMouseEvent*)), 
		paintOperator, SLOT(mouseMoved(QMouseEvent*)));

	connect(grayPaintCanvas, SIGNAL(mouseReleased(QMouseEvent*)), 
		paintOperator, SLOT(mouseReleased(QMouseEvent*)));

	connect(paintOperator, SIGNAL(newProcess(SharedProcess)), 
		this, SLOT(addProcess(SharedProcess)));

}

void VoiciMainWindow::saveFile(const QString &filename)
{
	QImage image = currentImageFamily->getCurrentImage();
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
	process->applyToImageFamily(currentImageFamily);
/*
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
*/	

}

void VoiciMainWindow::paintCanvasChanged()
{
	if (displayPanel->currentWidget() == grayPaintCanvas) {
		currentImageFamily = grayImageFamily;
		currentPaintCanvas = grayPaintCanvas;
	}
	else if (displayPanel->currentWidget() == paintCanvas) {
		currentImageFamily = imageFamily;
		currentPaintCanvas = paintCanvas;
	}
}

void VoiciMainWindow::setCanUndoAndRedo(bool canUndo, bool canRedo)
{
	undoAction->setEnabled(canUndo);
	redoAction->setEnabled(canRedo);
}

QImage VoiciMainWindow::getCurrentImage() const
{
	if (currentImageFamily != 0)
		return currentImageFamily->getCurrentImage();
	else
		return QImage();
}

QSharedPointer<IteratorArea> VoiciMainWindow::getArea() const
{
	return area;
}

void VoiciMainWindow::selectRectangle()
{
	paintOperator->setState(PaintOperator::SelectRectangle);
}

void VoiciMainWindow::selectCircle()
{
	paintOperator->setState(PaintOperator::SelectCircle);
}

void VoiciMainWindow::setIteratorArea(IteratorArea *area)
{
	this->area = QSharedPointer<IteratorArea>(area);
}

void VoiciMainWindow::setSelectedFilter(const QString &filter)
{
	m_filter = filter;
}
