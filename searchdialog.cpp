#include "searchdialog.h"

searchdialog::searchdialog(QWidget* parent): QDialog(parent){
	setWindowTitle("Ricerca delle chitare in magazzino");
	setModal(true);
	modelloS= new QLineEdit();
	modelloS->setText("undefined");
	cordeS=new QSpinBox();
	cordeS->setAccelerated(true);
    cordeS->setValue(6);
    cordeS->setRange(4,12);
	tipologiaS= new QComboBox();
	tipologiaS->insertItem(1,"acustica");
    tipologiaS->insertItem(2,"electrica");
	pricelS= new QDoubleSpinBox();
	pricelS->setAccelerated(true);
    pricelS->setValue(0);
    pricelS->setRange(0,1000000);
	pricehS= new QDoubleSpinBox();
	pricehS->setAccelerated(true);
    pricehS->setValue(0);
    pricehS->setRange(0,1000000);
	amplS= new QCheckBox();
	amplS->setText("amplificabile");
	ponteS= new QLineEdit();
	ponteS->setText("undefined");
    ponteS->setEnabled(false);
	pickupS= new QLineEdit();
	pickupS->setText("undefined");
    pickupS->setEnabled(false);
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(modelloS);
	layout->addWidget(cordeS);
	layout->addWidget(tipologiaS);
	layout->addWidget(pricelS);
	layout->addWidget(pricehS);
	layout->addWidget(amplS);
	layout->addWidget(ponteS);
	layout->addWidget(pickupS);
	setLayout(layout);
}