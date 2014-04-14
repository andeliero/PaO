#include "elementdialog.h"

elementdialog::elementdialog(controller* cn, QWidget* parent): QDialog(parent), cnt(cn) {
	lmn= new element(-1,0,this);
	QLabel* l1=new QLabel("Nome Modello",this);
	QLabel* l2=new QLabel("Corde",this);
	QLabel* l3=new QLabel("Tipologia",this);
	QLabel* l4=new QLabel("Prezzo",this);
	QLabel* l5=new QLabel("Amplificabile",this);
	QLabel* l6=new QLabel("Ponte",this);
	QLabel* l7=new QLabel("PickUp",this);
	ok=new QPushButton("Ok",this);
	cnc=new QPushButton("Cancel",this);
	QGridLayout* layout = new QGridLayout(this);	
	layout->addWidget(l1,0,0);
	layout->addWidget(l2,0,1);
	layout->addWidget(l3,0,2);
	layout->addWidget(l4,0,3);
	layout->addWidget(l5,0,4);
	layout->addWidget(l6,0,5);
	layout->addWidget(l7,0,6);
	layout->addWidget(lmn->getModelloW(),1,0);
	layout->addWidget(lmn->getCordeW(),1,1);
	layout->addWidget(lmn->getTypeW(),1,2);
	layout->addWidget(lmn->getPriceW(),1,3);
	layout->addWidget(lmn->getAmplW(),1,4);
	layout->addWidget(lmn->getBridgeW(),1,5);
	layout->addWidget(lmn->getPickUpW(),1,6);
	layout->addWidget(ok,2,5);
	layout->addWidget(cnc,2,6);
	setLayout(layout);
	connect(cnc,SIGNAL(clicked()),this,SLOT(close()));
	connect(ok,SIGNAL(clicked()),this,SLOT(addElement()));
}

void elementdialog::addElement(){
	if(lmn->getModello().isEmpty() || (lmn->getType()==QString("electrica") && (lmn->getBridge().isEmpty() || lmn->getPickUp().isEmpty()))){
		QMessageBox::critical(this,"Errore","Presenti Campi vuoti");
	}else{
		cnt->addGuitar(lmn);
		emit close();
	}
}