#ifndef VOICI_H
#define VOICI_H

#include <QMainWindow>

#include "Process.h"
#include "ImageFamily.h"

class QLabel;
class QToolBar;
class QAction;

class PaintCanvas;
class HistogramPanel;
class ConvolutionPanel;
class AlgebraicProcessPanel;
class ProcessPanel;

class VoiciMainWindow : public QMainWindow {
	Q_OBJECT
public:
	VoiciMainWindow();
	~VoiciMainWindow();
	void loadFile(const QString &filename);
	void saveFile(const QString &filename);

private slots:
 	void open();
	void save();
	void addProcess(SharedProcess process);
	void paintCanvasChanged();
private:
	void createToolBars();
	void createActions();
	void createCentralWidget();
	template <class T, class U>
	static void replaceTabWidget(QTabWidget *tabWidget, T **oldWidget, 
				     U *newWidget, const QString &label);
	
	QToolBar *fileToolBar;
	PaintCanvas *paintCanvas;
	PaintCanvas *grayPaintCanvas;

	HistogramPanel *histogramPanel;
	ConvolutionPanel *convolutionPanel;
	AlgebraicProcessPanel *algebraicProcessPanel;
	ProcessPanel *processPanel;

	QTabWidget *displayPanel;
	QTabWidget *controlPanel;

	QAction *openAction;
	QAction *saveAction;

	ImageFamily *imageFamily;
	ImageFamily *grayImageFamily;
	ImageFamily *currentImageFamily;

	QString currentFileName;
};

#endif
