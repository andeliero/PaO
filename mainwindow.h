#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QApplication>
#include <QPushButton>
#include <QAction>
#include <QMenuBar>
#include <QStatusBar>
#include <QMenu>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include "controller.h"
#include "elementdialog.h"
#include "searchdialog.h"
#include "table.h"
#include <iostream>
using std::cout;
using std::endl;

class controller;

class table;

class mainwindow: public QMainWindow{
	Q_OBJECT
private:
	controller* cnt;
	bool mod;
	QString file;
	QMenu* Menu;
	QAction* New;
	QAction* Close;
	QAction* Open;
	QAction* Save;
	QAction* SaveAs;
	QAction* Exit;
	QMenu* MenuT;
	QAction* NRow;
	QAction* DRow;
	QMenu* MenuS;
	QAction* Search;
	QAction* CloseSearch;
	QStatusBar* sttbar;
	table* tbl;
public:
	mainwindow( QWidget* );
public slots:
	void newFile();
	void closeFile();
	void openFile();
	void saveFile();
	void saveasFile();
	void activeSearch();
	//void closeSearch();
	void changeState();
	void addElement();
};

#endif