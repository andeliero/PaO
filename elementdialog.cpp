#include "elementdialog.h"

elementdialog::elementdialog(essemu* sm, QWidget* parent): QDialog(parent), shop(sm) {
    if(!shop) throw error("elementdialog(): essemu vuoto");

    nlm= new newelement(this);

	QLabel* l1=new QLabel("Nome Modello",this);
    QLabel* l2=new QLabel("Tipologia",this);
    QLabel* l3=new QLabel("Corde",this);
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
    layout->addWidget(nlm,1,0,1,7);

	layout->addWidget(ok,2,5);
	layout->addWidget(cnc,2,6);
	setLayout(layout);
	connect(cnc,SIGNAL(clicked()),this,SLOT(close()));
	connect(ok,SIGNAL(clicked()),this,SLOT(addElement()));
}


void elementdialog::addElement(){
    if(!nlm->isComplete()){
        QMessageBox::critical(this,"Errore","Presenti Campi vuoti");
    }else{
        switch (nlm->gettipologia()) {
        case 0:
            shop->insertGtr(acoustic(nlm->getmodello().toStdString(),nlm->getcorde(),nlm->getprezzo(),nlm->getampl(),nlm->getponte().toStdString()));
            break;
        case 1:
            shop->insertGtr(electric(nlm->getmodello().toStdString(),nlm->getcorde(),nlm->getprezzo(),nlm->getponte().toStdString(),nlm->getpickup().toStdString()));
            break;
        default:
            break;
        }
		QDialog::close();
        emit addedelement();
    }
}

void elementdialog::close(){
	QDialog::close();
}
