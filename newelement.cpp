#include "newelement.h"

newelement::newelement(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout* lay= new QHBoxLayout(this);
    modello= new QLineEdit(this);

    corde= new QSpinBox(this);
    corde->setAccelerated(true);
    corde->setRange(4,12);

    price= new QDoubleSpinBox(this);
    price->setAccelerated(true);
    price->setRange(0,1000000);

    tipologia= new QComboBox(this);
    tipologia->insertItem(0,"acustica");
    tipologia->insertItem(1,"elettrica");

    ampl= new QCheckBox(this);
    ampl->setText("amplificabile");
    ampl->setEnabled(true);

    ponte= new QLineEdit(parent);

    pickup= new QLineEdit(parent);
    pickup->setEnabled(false);

    lay->addWidget(modello);
    lay->addWidget(tipologia);
    lay->addWidget(corde);
    lay->addWidget(price);

    lay->addWidget(ampl);
    lay->addWidget(ponte);
    lay->addWidget(pickup);
    setLayout((lay));

    connect(tipologia,SIGNAL(currentIndexChanged(int)),this,SLOT(changeElement(int)));
}

bool newelement::isComplete() const{
    if(tipologia->currentIndex()==0){
            if(modello->text().isEmpty() || ponte->text().isEmpty()){
                return false;
            }
    }
    else{
        if(tipologia->currentIndex()==1){
                if(modello->text().isEmpty() || ponte->text().isEmpty() || pickup->text().isEmpty()){
                    return false;
                }
        }
    }
    return true;
}

QString newelement::getmodello() const{
    return modello->text();
}

int newelement::getcorde() const{
    return corde->value();
}

int newelement::gettipologia() const{
    return tipologia->currentIndex();
}

double newelement::getprezzo() const{
    price->value();
}

bool newelement::getampl() const{
    return ampl->isChecked();
}


QString newelement::getponte() const{
    return ponte->text();
}

QString newelement::getpickup() const{
    return pickup->text();
}



void newelement::changeElement(int a)
{
    if(a==0){
        ampl->setCheckState(Qt::Unchecked);
        ampl->setEnabled(true);
        pickup->setText("");
        pickup->setEnabled(false);
    }
    if(a==1){
        ampl->setCheckState(Qt::Checked);
        ampl->setEnabled(false);
        pickup->setText("");
        pickup->setEnabled(true);
    }
}
