#ifndef ELEMENT_H
#define ELEMENT_H
#include <QtGui>
#include <QString>
#include <string>
#include "essemu.h"
#include "guitar.h"
#include "electric.h"
#include "acoustic.h"
using std::string;


class guitar;
class acoustic;
class electric;

class element: public QObject{
	Q_OBJECT
private:
	essemu* shop;
	guitar* gtr;
	int row;
	QLineEdit* modello;
    QSpinBox* corde;
    QComboBox* tipologia;
    QDoubleSpinBox* price;
    QCheckBox* ampl;
    QLineEdit* ponte;
    QLineEdit* pickup;
public:
    explicit element(int ,essemu* ,guitar* ,QWidget* =0);
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
	void setRow(int);
	int getRow()const;
    guitar* getGuitar()const;
public slots:
	void changeElement(int);
    void changeModel(const QString&);
    void changeCorde(int);
    void changePrice(double);
    void changeAmpl(int);
    void changePonte(const QString&);
    void changePickUp(const QString&);
signals:
	void change();
};

#endif
