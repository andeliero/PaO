#include "controller.h"

controller::controller() : shop(0), wiv(0), tbv(0), tbdtv() {}

void controller::newShop(){
	shop=new essemu();
}

void controller::closeShop(){
	delete shop;
	shop=0;
	tbv=0;
}

void controller::openShop(QString fl){
	shop=new essemu();
	shop->openXml(fl);
}

void controller::saveShop(QString fl){
	shop->saveXml(fl);
}

void controller::setWindow(mainwindow* mw){
	wiv=mw;
}

void controller::setTable(table* tb){
	tbv=tb;
}

void controller::addGuitar(element* lm){
	if(lm->getType()==QString("electrica")){
		string model=lm->getModello().toStdString();
		int corde=lm->getCorde();
		double price=lm->getPrice();
		string ponte=lm->getBridge().toStdString();
		string pickup=lm->getPickUp().toStdString();
		electric* elc= new electric(model,corde,price,ponte,pickup);
		shop->insertGtr(elc);
	}
	if(lm->getTypeW()->currentText()==QString("acustica")){
		string model=lm->getModello().toStdString();
		int corde=lm->getCorde();
		double price=lm->getPrice();
		bool amp=lm->getAmpl();
		acoustic* ac= new acoustic(model,corde,price,amp);
		shop->insertGtr(ac);
	}
	deque<guitar*> all = shop->getAllGtr();
	tbdtv.clear();
	for(int i=0; i<all.size(); ++i){
		cout<<i<<" ";
		element* lmn=new element(i,this,tbv,all[i]);
		tbdtv.push_back(lmn);
	}
	tbv->refreshRows(tbdtv);
}

void controller::removeGuitar(element* lm){
	if(lm->getType()==QString("electrica")){
		string model=lm->getModello().toStdString();
		int corde=lm->getCorde();
		double price=lm->getPrice();
		string ponte=lm->getBridge().toStdString();
		string pickup=lm->getPickUp().toStdString();
		electric elc(model,corde,price,ponte,pickup);
		shop->removeGtr(elc);
	}
	if(lm->getTypeW()->currentText()==QString("acustica")){
		string model=lm->getModello().toStdString();
		int corde=lm->getCorde();
		double price=lm->getPrice();
		bool amp=lm->getAmpl();
		acoustic ac(model,corde,price,amp);
		shop->removeGtr(ac);
	}
	deque<guitar*> all = shop->getAllGtr();
	tbdtv.clear();
	for(int i=0; i<all.size(); ++i){
		cout<<i<<" ";
		element* lmn=new element(i,this,tbv,all[i]);
		tbdtv.push_back(lmn);
	}
	tbv->refreshRows(tbdtv);
}

