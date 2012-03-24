#include <QApplication>

#include "VoiciMainWindow.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	VoiciMainWindow mainWindow;
	mainWindow.show();
	return app.exec();
}
