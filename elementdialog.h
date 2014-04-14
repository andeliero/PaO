#ifndef ELEMENTDIALOG_H
#define ELEMENTDIALOG_H
#include <QDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QSpacerItem>
#include <QLineEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QLabel>
#include "element.h"
#include "controller.h"

class element;

class controller;

class elementdialog: public QDialog{
Q_OBJECT
private:
	controller* cnt;
	element* lmn;
	QPushButton* ok;
	QPushButton* cnc;
public:
	elementdialog(controller*,QWidget*);
public slots:
	void addElement();
};

#endif