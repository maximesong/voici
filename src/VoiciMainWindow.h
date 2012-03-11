#ifndef VOICI_H
#define VOICI_H

#include <QMainWindow>

class QLabel;
class QToolBar;
class QAction;

class PaintCanvas;

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
	void loadFile(const QString &filename);
	
	QToolBar *fileToolBar;
	PaintCanvas *imageLabel;

	QAction *openAction;
	QAction *saveAction;

	QString currentFileName;
};

#endif
