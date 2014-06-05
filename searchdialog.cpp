#include "searchdialog.h"

searchdialog::searchdialog(table* tb,essemu* sm,QWidget* parent): QDialog(parent), shop(sm), tbl(tb) {
    setWindowTitle("Ricerca delle chitare in magazzino");
	setModal(true);
    modello= new QLineEdit(this);

    cordeL=new QSpinBox(this);
    cordeL->setAccelerated(true);
    cordeL->setRange(4,12);
    cordeU=new QSpinBox(this);
    cordeU->setAccelerated(true);
    cordeU->setRange(4,12);
    cordeU->setValue(12);

    tipologia= new QComboBox(this);
    tipologia->insertItem(0,"acoustic");
    tipologia->insertItem(1,"electric");
    tipologia->insertItem(2,"");

    priceL= new QDoubleSpinBox(this);
    priceL->setAccelerated(true);
    priceL->setRange(0,1000000);
    priceU= new QDoubleSpinBox(this);
    priceU->setAccelerated(true);
    priceU->setRange(0,1000000);

    ampl= new QCheckBox(this);
    ampl->setText("amplificabile");
    ponte= new QLineEdit(this);
    pickup= new QLineEdit(this);
    pickup->setEnabled(false);


    QGridLayout* layout = new QGridLayout(this);

    QLabel* l1=new QLabel("Nome Modello",this);
    QLabel* l2=new QLabel("Tipologia",this);
    QLabel* l3=new QLabel("Corde",this);
    QLabel* l4=new QLabel("Prezzo",this);
    QLabel* l5=new QLabel("Amplificabile",this);
    QLabel* l6=new QLabel("Ponte",this);
    QLabel* l7=new QLabel("PickUp",this);
    QPushButton* ok=new QPushButton("Ok",this);
    QPushButton* cnc=new QPushButton("Cancel",this);

    layout->addWidget(l1,0,0);
    layout->addWidget(l2,0,1);
    layout->addWidget(l3,0,2);
    layout->addWidget(l4,0,3);
    layout->addWidget(l5,0,4);
    layout->addWidget(l6,0,5);
    layout->addWidget(l7,0,6);

    layout->addWidget(modello,1,0);
    layout->addWidget(cordeL,1,1);
    layout->addWidget(cordeU,2,1);
    layout->addWidget(tipologia,1,2);
    layout->addWidget(priceL,1,3);
    layout->addWidget(priceU,2,3);
    layout->addWidget(ampl,1,4);
    layout->addWidget(ponte,1,5);
    layout->addWidget(pickup,1,6);

    layout->addWidget(ok,3,5);
    layout->addWidget(cnc,3,6);


    setLayout(layout);

    connect(tipologia,SIGNAL(currentIndexChanged(int)),this,SLOT(changetype(int)));
    connect(cnc,SIGNAL(clicked()),this,SLOT(close()));
    connect(ok,SIGNAL(clicked()),this,SLOT(searchok()));
}

void searchdialog::changetype(int a){
    if(a==0){
        ampl->setEnabled(true);
        ampl->setChecked(false);

        pickup->setText("");
        pickup->setEnabled(false);
    }
    if(a==1){
        ampl->setEnabled(false);
        ampl->setChecked(true);

        pickup->setEnabled(true);
    }
    if(a==2){
        ampl->setEnabled(true);

        pickup->setEnabled(true);
    }
}

void searchdialog::searchok(){
    tbl->getsearch(shop->searchgtrs(
                       cordeL->value(),
                       cordeU->value(),
                       priceL->value(),
                       priceU->value(),
                       ampl->isChecked(),
                       modello->text().toStdString(),
                       ponte->text().toStdString(),
                       tipologia->currentText().toStdString(),
                       pickup->text().toStdString()
                                    ));
    QDialog::close();
}
