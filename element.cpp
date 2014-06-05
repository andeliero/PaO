#include "element.h"


element::element(int ro, essemu* cn,guitar* gt ,QWidget* parent): QObject(parent), shop(cn), gtr(gt){
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
    tipologia->insertItem(0,"acustica");
    tipologia->insertItem(1,"elettrica");

    ampl= new QCheckBox(parent);
    ampl->setText("amplificabile");
    if(gtr->amplf())
    	ampl->setCheckState(Qt::Checked);
    else
        ampl->setCheckState(Qt::Unchecked);

    ponte= new QLineEdit(parent);

    pickup= new QLineEdit(parent);
    pickup->setEnabled(false);

    electric* el=dynamic_cast<electric*>(gtr);
    acoustic* ac=dynamic_cast<acoustic*>(gtr);
    if(el){
    	tipologia->setCurrentIndex(1);
    	ampl->setEnabled(false);
    	ponte->setText(QString::fromStdString(el->get_ponte()));
		pickup->setText(QString::fromStdString(el->get_pickup()));
		pickup->setEnabled(true);
    }
    if(ac){
    	tipologia->setCurrentIndex(0);
        ponte->setText(QString::fromStdString(ac->get_ponte()));
		pickup->setEnabled(false);
    }

    connect(modello,SIGNAL(textChanged( const QString &)),this,SLOT(changeModel(const QString&)));
    connect(modello,SIGNAL(textChanged( const QString &)),this,SIGNAL(change()));
    connect(corde,SIGNAL(valueChanged(int)),this,SLOT(changeCorde(int)));
	connect(corde,SIGNAL(valueChanged(int)),this,SIGNAL(change()));
    connect(price,SIGNAL(valueChanged(double)),this,SLOT(changePrice(double)));
	connect(price,SIGNAL(valueChanged(double)),this,SIGNAL(change()));
    connect(tipologia,SIGNAL(currentIndexChanged(int)),this,SLOT(changeElement(int)));
    connect(ampl,SIGNAL(stateChanged(int)),this,SLOT(changeAmpl(int)));
    connect(ampl,SIGNAL(stateChanged(int)),this,SIGNAL(change()));
    connect(ponte,SIGNAL(textChanged( const QString &)),this,SLOT(changePonte(const QString&)));
    connect(ponte,SIGNAL(textChanged( const QString &)),this,SIGNAL(change()));
    connect(pickup,SIGNAL(textChanged( const QString &)),this,SLOT(changePickUp(const QString &)));
    connect(pickup,SIGNAL(textChanged( const QString &)),this,SIGNAL(change()));
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
		pickup->setEnabled(true);
        electric* el=new electric(gtr->get_name(),gtr->get_corde(),gtr->get_price(),gtr->get_ponte(),"undefined");
        shop->replaceGtr(gtr,el);
        gtr=el;
	}
	if(a==0){
		ampl->setCheckState(Qt::Unchecked);
		ampl->setEnabled(true);
        pickup->setText("undefined");
		pickup->setEnabled(false);
        acoustic* ac= new acoustic(gtr->get_name(),gtr->get_corde(),gtr->get_price(),false,gtr->get_ponte());
        shop->replaceGtr(gtr,ac);
        gtr=ac;
    }
    emit change();
}

void element::changeModel(const QString& qst){
    gtr->set_name(qst.toStdString());
}

void element::changeCorde(int cr){
    gtr->set_corde(cr);
}

void element::changePrice(double pr){
    gtr->set_price(pr);
}

void element::changeAmpl(int b){
    acoustic* ac= dynamic_cast<acoustic*>(gtr);
    if(ac)  ac->set_amplf(b);
}

void element::changePonte(const QString& str){
    electric* el=dynamic_cast<electric*>(gtr);
    acoustic* ac=dynamic_cast<acoustic*>(gtr);
    if(el)  el->set_ponte(str.toStdString());
    if(ac)  ac->set_ponte(str.toStdString());
}

void element::changePickUp(const QString& str){
    electric* el=dynamic_cast<electric*>(gtr);
    if(el)  el->set_pickup(str.toStdString());
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

void element::setRow(int i){
    row=i;
}

int element::getRow()const{
    return row;
}

guitar* element::getGuitar()const{
    return gtr;
}
