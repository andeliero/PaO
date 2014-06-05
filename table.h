#ifndef TABLE_H
#define TABLE_H
#include <QtGui>
#include <QStringList>
#include "essemu.h"
#include "deque.h"
#include "element.h"

class element;

class table: public QTableWidget{
	Q_OBJECT
private:
	essemu* shop;
	deque<element*> rodt;
    void insertRow(element*);
public:
	table( QWidget* , essemu*);
	~table();
    void getsearch(deque<int> idx);
public slots:

	void removeRow();
    void refresh();
signals:
	void changed();
};

#endif
