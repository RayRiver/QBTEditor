#include "mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(mainwindow);

	QApplication a(argc, argv);
	MainWindow w;
	w.setGeometry(200, 100, 1200, 750);
	w.show();
	return a.exec();
}
