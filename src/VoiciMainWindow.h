#ifndef VOICI_H
#define VOICI_H

#include <QMainWindow>

class QLabel;
class QToolBar;
class QAction;

class PaintCanvas;
class HistogramPanel;
class ConvolutionPanel;
class ImageCore;
class GrayImageCore;

class VoiciMainWindow : public QMainWindow {
	Q_OBJECT
public:
	VoiciMainWindow();
	~VoiciMainWindow();

private slots:
 	void open();
	void save();
private:
	void createToolBars();
	void createActions();
	void createCentralWidget();
	void loadFile(const QString &filename);
	template <class T, class U>
	static void replaceTabWidget(QTabWidget *tabWidget, T **oldWidget, 
				     U *newWidget, const QString &label);
	
	QToolBar *fileToolBar;
	PaintCanvas *paintCanvas;
	PaintCanvas *grayPaintCanvas;

	HistogramPanel *histogramPanel;
	ConvolutionPanel *convolutionPanel;

	QTabWidget *displayPanel;
	QTabWidget *controlPanel;

	QAction *openAction;
	QAction *saveAction;

	ImageCore *imageCore;
	ImageCore *grayImageCore;

	QString currentFileName;
};

#endif
