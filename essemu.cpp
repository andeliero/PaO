#include "essemu.h"

essemu::essemu(){
	cout<<"Ha creato il magazzino."<<endl;
}

essemu::~essemu(){
	cout<<"Distrutto il magazzino."<<endl;
	for(deque<guitar*>::iterator it = mag.begin(); it!= mag.end(); ++it){
		delete (*it);
	}
}

void essemu::insertGtr(guitar* gtr){
	electric* ec = dynamic_cast<electric*>(gtr);
	if(ec)
		cout<<"inserito una chitarra elettrica."<<endl;
	acoustic* ac = dynamic_cast<acoustic*>(gtr);
	if(ac)
		cout<<"inserito una chitarra acustica."<<endl;
	mag.push_front(gtr);
	//sortbyName(); //forse si può utilizzare nell'ordinamento di colonna della tabella
}

void essemu::changeGtr(int pos,int tp){
	guitar* gt=mag[pos];
	electric* elt = dynamic_cast<electric*>(gt);
	acoustic* ac = dynamic_cast<acoustic*>(gt);
	if(elt && tp==0){
		guitar* a=gt;
		gt=new acoustic(a->get_name(),a->get_corde(),a->get_price(),false);
		delete a;
	}
	if(ac && tp==1){
		guitar* a=gt;
		gt=new electric(a->get_name(),a->get_corde(),a->get_price(),"undefined","undefined");
		delete a;
	}
	cout<<"Cambiato il tipo."<<endl;
}

guitar* essemu::getGtr(int pos)const{
	return mag[pos];
}

void essemu::saveXml(QString fl){
	cout<<"Salvato XML."<<endl;
}

void essemu::openXml(QString fl){
	cout<<"Aperto XML."<<endl;
}

void essemu::sortbyName(){
	int i, j, n = mag.size();
	guitar* key;
	for (j = 1; j < n; j++){ 
		key = mag[j];
		i=j-1;
		while (i >= 0 && mag[i]->get_name() > key->get_name()){
			mag[i+1] = mag[i]; 
			i--;
		}
		mag[i+1] = key;
	}
}

void essemu::removeGtr(const guitar& gtr){
	bool found=false;
	for (int i = 0; i < mag.size() && !found; ++i){
		if(*mag[i]==gtr){
			mag.deleteAt(i);//revisionare
			found=true;
		}
	}
}

deque<guitar*> essemu::getAllGtr()const{
	return mag;
}