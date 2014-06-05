#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H
#include <QtGui>
#include "table.h"

class searchdialog: public QDialog{
	Q_OBJECT
private:
    QLineEdit* modello;
    QSpinBox* cordeL;
    QSpinBox* cordeU;
    QComboBox* tipologia;
    QDoubleSpinBox* priceL;
    QDoubleSpinBox* priceU;
    QCheckBox* ampl;
    QLineEdit* ponte;
    QLineEdit* pickup;
    table* tbl;
    essemu* shop;
public:
    searchdialog(table *tb, essemu* sm,QWidget* =0);
private slots:
    void changetype(int);
    void searchok();
};

#endif
