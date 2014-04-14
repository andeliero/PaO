#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "mainwindow.h"
#include "table.h"
#include "element.h"
#include "essemu.h"
#include "deque.h"
#include <QString>
#include <iostream>
using std::cout;
using std::endl;

class mainwindow;
class table;
class element;

class controller{
private:
	essemu* shop;
	mainwindow* wiv;
	table* tbv;
	deque<element*> tbdtv;
public:
	controller();
	void newShop();
	void saveShop(QString);
	void openShop(QString);
	void closeShop();
	void setWindow(mainwindow*);
	void setTable(table*);
	void addGuitar(element*);
	void removeGuitar(element*);
};

#endif