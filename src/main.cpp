#include <QApplication>
#include <QTranslator>

#include "VoiciMainWindow.h"

VoiciMainWindow *mainWindow;

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	#ifdef LANGUAGE_ZH
	QTranslator translator;
	translator.load(":/languages/voici_zh");
	app.installTranslator(&translator);
	#endif

	mainWindow = new VoiciMainWindow();
	mainWindow->show();

	#ifdef QUICK_TEST
	mainWindow->loadFile("test1.jpg");
	#endif

	return app.exec();
}
