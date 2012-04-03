#include <QApplication>
#include <QTranslator>

#include "VoiciMainWindow.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	QTranslator translator;
	translator.load("languages/voici_zh");
	app.installTranslator(&translator);

	VoiciMainWindow mainWindow;
	mainWindow.show();
	mainWindow.loadFile("test1.jpg");
	return app.exec();
}
