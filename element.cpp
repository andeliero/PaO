#include "element.h"

element::element(int ro,controller* cn,QWidget* parent): QObject(parent), cnt(cn){
	row=ro;
	modello= new QLineEdit(parent);	
	connect(modello,SIGNAL(textChanged( const QString &)),this,SIGNAL(change()));
    corde= new QSpinBox(parent);
    corde->setAccelerated(true);
    corde->setRange(4,12);
    connect(corde,SIGNAL(valueChanged(int)),this,SIGNAL(change()));
    tipologia= new QComboBox(parent);
    tipologia->insertItem(1,"acustica");
    tipologia->insertItem(2,"electrica");
    connect(tipologia,SIGNAL(currentIndexChanged(int)),this,SLOT(changeElement(int)));
    price= new QDoubleSpinBox(parent);
    price->setAccelerated(true);
    price->setRange(0,1000000);
    connect(price,SIGNAL(valueChanged(double)),this,SIGNAL(change()));
    ampl= new QCheckBox(parent);
    ampl->setText("amplificabile");
    connect(ampl,SIGNAL(stateChanged(int)),this,SIGNAL(change()));
    ponte= new QLineEdit(parent);
    ponte->setEnabled(false);
    connect(ponte,SIGNAL(textChanged( const QString &)),this,SIGNAL(change()));
    pickup= new QLineEdit(parent);
    pickup->setEnabled(false);
    connect(pickup,SIGNAL(textChanged( const QString &)),this,SIGNAL(change()));
    if(cnt){
    	//connect varie
    }
}

element::element(int ro, controller* cn, QWidget* parent, guitar* gtr): QObject(parent), cnt(cn){
	row=ro;

	modello= new QLineEdit(parent);
	modello->setText(QString::fromStdString(gtr->get_name()));

    corde= new QSpinBox(parent);
    corde->setAccelerated(true);
    corde->setRange(4,12);
    corde->setValue(gtr->get_corde());
    
    price= new QDoubleSpinBox(parent);
    price->setAccelerated(true);
    price->setRange(0,1000000);
    price->setValue(gtr->get_price());

    tipologia= new QComboBox(parent);
    tipologia->insertItem(1,"acustica");
    tipologia->insertItem(2,"electrica");

    ampl= new QCheckBox(parent);
    ampl->setText("amplificabile");
    if(gtr->amplf())
    	ampl->setCheckState(Qt::Checked);
    else
    	ampl->setCheckState(Qt::Checked);

    ponte= new QLineEdit(parent);
    ponte->setEnabled(false);

    pickup= new QLineEdit(parent);
    pickup->setEnabled(false);

    electric* el=dynamic_cast<electric*>(gtr);
    acoustic* ac=dynamic_cast<acoustic*>(gtr);
    if(el){
    	tipologia->setCurrentIndex(1);
    	ampl->setEnabled(false);
    	ponte->setText(QString::fromStdString(el->get_ponte()));
		ponte->setEnabled(true);
		pickup->setText(QString::fromStdString(el->get_pickup()));
		pickup->setEnabled(true);
    }
    if(ac){
    	tipologia->setCurrentIndex(0);
    	ponte->setEnabled(false);
		pickup->setEnabled(false);
    }

    connect(modello,SIGNAL(textChanged( const QString &)),this,SIGNAL(change()));
	connect(corde,SIGNAL(valueChanged(int)),this,SIGNAL(change()));
	connect(price,SIGNAL(valueChanged(double)),this,SIGNAL(change()));
    connect(tipologia,SIGNAL(currentIndexChanged(int)),this,SLOT(changeElement(int)));
    connect(ampl,SIGNAL(stateChanged(int)),this,SIGNAL(change()));
    connect(ponte,SIGNAL(textChanged( const QString &)),this,SIGNAL(change()));
    connect(pickup,SIGNAL(textChanged( const QString &)),this,SIGNAL(change()));
    if(cnt){
    	//connect varie
    }
}

QLineEdit* element::getModelloW()const{
	return modello;
}

QSpinBox* element::getCordeW()const{
	return corde;
}

QComboBox* element::getTypeW()const{
	return tipologia;
}

QDoubleSpinBox* element::getPriceW()const{
	return price;
}

QCheckBox* element::getAmplW()const{
	return ampl;
}

QLineEdit* element::getBridgeW()const{
	return ponte;
}

QLineEdit* element::getPickUpW()const{
	return pickup;
}


void element::changeElement(int a){
	if(a==1){
		ampl->setCheckState(Qt::Checked);
		ampl->setEnabled(false);
		ponte->setEnabled(true);
		pickup->setEnabled(true);
	}
	if(a==0){
		ampl->setCheckState(Qt::Unchecked);
		ampl->setEnabled(true);
		ponte->setText("undefined");
		ponte->setEnabled(false);
		pickup->setText("undefined");
		pickup->setEnabled(false);
	}
	emit change();
}

QString element::getType()const{
	return tipologia->currentText();
}

QString element::getModello()const{
	return modello->text ();
}

int element::getCorde()const{
	return corde->value();
}
double element::getPrice()const{
	return price->value();
}

bool element::getAmpl()const{
	Qt::CheckState cs = ampl->checkState();
	if(cs==Qt::Checked)
		return true;
	else
		return false;
}

QString element::getBridge()const{
	return ponte->text();
}

QString element::getPickUp()const{
	return pickup->text();
}