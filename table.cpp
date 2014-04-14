#include "table.h"

table::table( QWidget * parent , controller* cn): QTableWidget(0,7,parent), cnt(cn),rodt() {
	QStringList sls;
	sls<<"Nome Modello"<<"N Corde"<<"Tipologia"<<"Prezzo"<<"Amplificabile"<<"Ponte"<<"PickUp";
	setHorizontalHeaderLabels(sls);
}

table::~table(){
	for(deque<element*>::iterator it=rodt.begin(); it!=rodt.end(); ++it){
		delete (*it);
	}
}

void table::addElement(){
	int a = currentRow();
	if(a<0) a=rowCount();
	insertRow(a);
	element* lmn= new element(a,cnt,this);
	connect(lmn,SIGNAL(change()),this,SIGNAL(changed()));
	rodt.push_back(lmn);
	setCellWidget(a,0, lmn->getModelloW() );
	setCellWidget(a,1, lmn->getCordeW() );
	setCellWidget(a,2, lmn->getTypeW() );
	setCellWidget(a,3, lmn->getPriceW() );
	setCellWidget(a,4, lmn->getAmplW() );
	setCellWidget(a,5, lmn->getBridgeW() );
	setCellWidget(a,6, lmn->getPickUpW() );
	setCurrentCell(a,0);
}

void table::refreshRows(deque<element*> dt){
	setRowCount(0);
	for (int i = 0; i < dt.size(); ++i){
		insertRow(i);
		connect(dt[i],SIGNAL(change()),this,SIGNAL(changed()));
		rodt.push_back(dt[i]);
		setCellWidget(i,0, dt[i]->getModelloW() );
		setCellWidget(i,1, dt[i]->getCordeW() );
		setCellWidget(i,2, dt[i]->getTypeW() );
		setCellWidget(i,3, dt[i]->getPriceW() );
		setCellWidget(i,4, dt[i]->getAmplW() );
		setCellWidget(i,5, dt[i]->getBridgeW() );
		setCellWidget(i,6, dt[i]->getPickUpW() );
		setCurrentCell(i,0);
	}
	update();

}

void table::remElement(){
	int a = currentRow();
	cnt->removeGuitar(rodt[a]);
}