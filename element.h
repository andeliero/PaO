#ifndef ELEMENT_H
#define ELEMENT_H
#include <QObject>
#include <QLineEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QCheckBox>

#include <string>
#include <QString>
#include <iostream>
#include "guitar.h"
#include "electric.h"
#include "acoustic.h"
#include "controller.h"
using std::cout;using std::endl;
using std::string;

class controller;
class guitar;
class acoustic;
class electric;

class element: public QObject{
	Q_OBJECT
private:
	controller* cnt;
	int row;
	QLineEdit* modello;
    QSpinBox* corde;
    QComboBox* tipologia;
    QDoubleSpinBox* price;
    QCheckBox* ampl;
    QLineEdit* ponte;
    QLineEdit* pickup;
public:
	element(int,controller*,QWidget*);
	element(int,controller*,QWidget*,guitar*);
	QLineEdit* getModelloW()const;
	QSpinBox* getCordeW()const;
	QComboBox* getTypeW()const;
	QDoubleSpinBox* getPriceW()const;
	QCheckBox* getAmplW()const;
	QLineEdit* getBridgeW()const;
	QLineEdit* getPickUpW()const;
	QString getType()const;
	QString getModello()const;
	int getCorde()const;
	double getPrice()const;
	bool getAmpl()const;
	QString getBridge()const;
	QString getPickUp()const;
public slots:
	void changeElement(int);
signals:
	void change();
};

#endif