#ifndef ELEMENTDIALOG_H
#define ELEMENTDIALOG_H
#include <QtGui>
#include "acoustic.h"
#include "electric.h"
#include "newelement.h"
#include "table.h"

class element;

class table;

class elementdialog: public QDialog{
Q_OBJECT
private:
	essemu* shop;
    newelement* nlm;
	QPushButton* ok;
	QPushButton* cnc;
public:
    elementdialog(essemu* ,QWidget* );
public slots:
	void addElement();
	void close();
signals:
    void addedelement();
};

#endif
