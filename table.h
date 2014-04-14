#ifndef TABLE_H
#define TABLE_H
#include <QTableWidget>
#include <QStringList>
#include "deque.h"
#include "controller.h"
#include "element.h"

class controller;
class element;

class table: public QTableWidget{
	Q_OBJECT
private:
	controller* cnt;
	deque<element*> rodt;
public:
	table( QWidget* , controller*);
	~table();
	void refreshRows(deque<element*>);
public slots:
	void addElement();
	void remElement();
signals:
	void changed();
};

#endif