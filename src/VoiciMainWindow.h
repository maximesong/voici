#ifndef VOICI_H
#define VOICI_H

#include <QMainWindow>

#include "Process.h"
#include "ImageFamily.h"

#include <QLabel>
#include <QAction>
#include <QToolBar>
#include <QVector>
#include <QPoint>
#include <QSharedPointer>

class PaintCanvas;
class HistogramPanel;
class ConvolutionPanel;
class MorphologyPanel;
class AlgebraicProcessPanel;
class ProcessPanel;

class IteratorArea;
class PaintOperator;

class VoiciMainWindow : public QMainWindow {
	Q_OBJECT
public:
	VoiciMainWindow();
	~VoiciMainWindow();
	void loadFile(const QString &filename);
	void saveFile(const QString &filename);

	QImage getCurrentImage() const;
	QSharedPointer<IteratorArea> getArea() const;
private slots:
 	void open();
	void save();
	void undo();
	void redo();
	void selectRectangle();
	void selectCircle();
	void addProcess(SharedProcess process);
	void paintCanvasChanged();
	void setCanUndoAndRedo(bool canUndo, bool canRedo);
	void setIteratorArea(IteratorArea *area);
	void setSelectedFilter(const QString &filter);
private:
	void createToolBars();
	void createActions();
	void createCentralWidget();
	template <class T, class U>
	static void replaceTabWidget(QTabWidget *tabWidget, T **oldWidget, 
				     U *newWidget, const QString &label);
	
	PaintOperator *paintOperator;

	QToolBar *fileToolBar;
	PaintCanvas *paintCanvas;
	PaintCanvas *grayPaintCanvas;
	PaintCanvas *currentPaintCanvas;

	HistogramPanel *histogramPanel;
	ConvolutionPanel *convolutionPanel;
	MorphologyPanel *morphologyPanel;
	AlgebraicProcessPanel *algebraicProcessPanel;
	ProcessPanel *processPanel;

	QTabWidget *displayPanel;
	QTabWidget *controlPanel;

	QAction *openAction;
	QAction *saveAction;
	QAction *redoAction;
	QAction *undoAction;
	QAction *rectAction;
	QAction *circleAction;

	ImageFamily *imageFamily;
	ImageFamily *grayImageFamily;
	ImageFamily *currentImageFamily;

	QSharedPointer<IteratorArea> area;
	QString currentFileName;
	QString m_filter;
};

#endif
