#include <QApplication>
#include <QIcon>
#include "mainwindow.h"


int main(int argc, char* argv[]){
	QApplication app(argc,argv);
	app.setWindowIcon(QIcon("img/Icon.png"));
	mainwindow mw(0);
	mw.show();
	QObject::connect(qApp,SIGNAL(lastWindowClosed()),qApp,SLOT(quit()));
	return QApplication::exec();
}