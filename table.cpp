#include "table.h"

table::table( QWidget * parent , essemu* sm): QTableWidget(0,7,parent), shop(sm),rodt() {
	QStringList sls;
	sls<<"Nome Modello"<<"N Corde"<<"Tipologia"<<"Prezzo"<<"Amplificabile"<<"Ponte"<<"PickUp";
	setHorizontalHeaderLabels(sls);
}

table::~table(){
	for(deque<element*>::iterator it=rodt.begin(); it!=rodt.end(); ++it){
		delete (*it);
    }
}

void table::getsearch(deque<int> idx){
    for(int i=0; i<rowCount(); i++){
        setRowHidden(i,true);
    }
    for(int i=0; i<idx.size(); ++i){
        setRowHidden(idx[i],false);
    }
}

void table::insertRow(element* lmn){
    if(!lmn)    throw error("Inserimento di elemento vuoto");
	int a=rowCount();
	QTableWidget::insertRow(a);
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

void table::removeRow(){
    QModelIndexList lr= selectionModel()->selectedRows();
    for( int i=lr.count()-1; i>-1; i--){
        rodt.deleteAt(i);
        shop->removeGtr(i);
        QTableWidget::removeRow(i);
    }
}

void table::refresh(){
    deque<guitar*> gtrs=shop->getAllGtr();

    for(int a=rowCount(); a>=0; --a){
        QTableWidget::removeRow(a);
    }

    for(deque<element*>::iterator it=rodt.begin(); it!=rodt.end(); ++it){
        delete (*it);
    }
    rodt.clear();

    for(deque<guitar*>::const_iterator it = gtrs.cbegin(); it!=gtrs.cend(); ++it){
        element* lm=new element(rowCount(),shop,*it,this);
        insertRow(lm);
    }
}
