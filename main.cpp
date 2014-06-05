#include <QApplication>
#include <QIcon>
#include "essemu.h"
#include "mainwindow.h"


int main(int argc, char* argv[]) try {
	QApplication app(argc,argv);
	app.setWindowIcon(QIcon("img/Icon.png"));
    essemu shop;
    mainwindow mw(shop,0);
	mw.show();
	QObject::connect(qApp,SIGNAL(lastWindowClosed()),qApp,SLOT(quit()));
	return QApplication::exec();
}catch(error e){
    cout<<e.getMsg()<<endl;
}
