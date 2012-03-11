#ifndef VOICI_H
#define VOICI_H

#include <QMainWindow>

class QLabel;
class QToolBar;
class QAction;

class PaintCanvas;
class Histogram;

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
	
	QToolBar *fileToolBar;
	PaintCanvas *paintCanvas;
	Histogram *histogram;

	QAction *openAction;
	QAction *saveAction;

	QString currentFileName;
};

#endif
