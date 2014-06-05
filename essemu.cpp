#include "essemu.h"

essemu::essemu(): mag(), file(""), changed(false){
}

essemu::~essemu(){
	deleteAll();
}

string essemu::getFilename()const{
    return file;
}

bool essemu::isChanged() const{
    return changed;
}

void essemu::setChanged(bool a){
    changed=a;
}

void essemu::deleteAll(){
	for(deque<guitar*>::iterator it = mag.begin(); it!= mag.end(); ++it){
		delete (*it);
	}
    mag.clear();
}

bool essemu::isEmpty() const
{
    return mag.empty();
}

void essemu::insertGtr(const guitar &gtr){
    guitar& gt= const_cast<guitar&>(gtr);
    electric* el= dynamic_cast<electric*>(&gt);
    if(el){
        cout<<el->get_name()<<el->get_ponte()<<endl;
        mag.push_back(new electric(*el));
    }else{
        acoustic* ac= dynamic_cast<acoustic*>(&gt);
        if(ac){
            mag.push_back(new acoustic(*ac));
            cout<<ac->get_name()<<ac->get_ponte()<<endl;
        }
    }
    changed=true;
}

void essemu::replaceGtr(guitar* act ,guitar* st){
    bool found=false;
    for(deque<guitar*>::iterator it=mag.begin(); it!=mag.end() && !found; ++it){
        if((*it)==act){
            delete (*it);
            (*it)=st;
            found=true;
        }
    }
}

guitar* essemu::getGtr(int pos)const{
	return mag[pos];
}

void essemu::saveXml(string fl=""){
    if(fl!="")
        file=fl;
    if(file=="")
		return;
    file=fl;
    QFile fil(QString::fromStdString(fl));
    fil.open(QIODevice::WriteOnly);
    QXmlStreamWriter composer(&fil);
	composer.setAutoFormatting(true);
	composer.writeStartDocument();
	composer.writeStartElement("QDb");
	for(deque<guitar*>::const_iterator it = mag.cbegin(); it!=mag.cend(); ++it){
		electric* el=dynamic_cast<electric*>(*it);
		acoustic* ac=dynamic_cast<acoustic*>(*it);
		if(el){
			composer.writeStartElement("electric");
			composer.writeTextElement("modello",QString::fromStdString((*it)->get_name()));
			composer.writeTextElement("corde",QString::number((*it)->get_corde()));
			composer.writeTextElement("prezzo",QString::number((*it)->get_price()));
			composer.writeTextElement("ponte",QString::fromStdString(el->get_ponte()));
			composer.writeTextElement("pickup",QString::fromStdString(el->get_pickup()));
			composer.writeEndElement();
		}
		if(ac){
			composer.writeStartElement("acoustic");
			composer.writeTextElement("modello",QString::fromStdString((*it)->get_name()));
			composer.writeTextElement("corde",QString::number((*it)->get_corde()));
			composer.writeTextElement("prezzo",QString::number((*it)->get_price()));
            composer.writeTextElement("amplificabile",QString::number((*it)->amplf()));
			composer.writeTextElement("ponte",QString::fromStdString(ac->get_ponte()));
			composer.writeEndElement();
		}
	}
	composer.writeEndElement();
	composer.writeEndDocument();
    changed=false;
}

void essemu::openXml(string fl){
    if(fl=="")
        throw(error("file vuoto"));
    file=fl;
    QFile fil(QString::fromStdString(fl));
    QXmlStreamReader xmlparser(&fil);
    if (fil.open(QIODevice::ReadOnly | QIODevice::Text))//QIODevice::Text serve per tradurre i caratteri speciali per il sistema corrente
    {
    if(mag.size())
    	deleteAll();
    QXmlStreamReader::TokenType token = xmlparser.readNext();
    if(token!=QXmlStreamReader::StartDocument)
        throw error("file vuoto o incompatibile con XML");
    while(!xmlparser.isEndDocument()){
        token = xmlparser.readNext();
		if(xmlparser.isStartElement()){
			if(xmlparser.name()=="electric"){
				string modello="";
				int corde=0;
				double prezzo=0;
				string ponte="";
				string pickup="";
				while(!xmlparser.isEndElement()){
					if(xmlparser.name()=="modello")
						modello=xmlparser.readElementText().toStdString();
					if(xmlparser.name()=="corde")
						corde=xmlparser.readElementText().toInt();
					if(xmlparser.name()=="prezzo")
						prezzo=xmlparser.readElementText().toDouble();
					if(xmlparser.name()=="ponte")
						ponte=xmlparser.readElementText().toStdString();
					if(xmlparser.name()=="pickup")
						pickup=xmlparser.readElementText().toStdString();
					xmlparser.readNext();
				}
				electric* el = new electric(modello,corde,prezzo,ponte,pickup);
				mag.push_back(el);
			}
			if(xmlparser.name()=="acoustic"){
				string modello="";
				int corde=0;
				double prezzo=0;
				bool amplf;
				string ponte="";
				while(!(xmlparser.tokenType()==xmlparser.EndElement)){//!xmlparser.isEndElement()){
					if(xmlparser.name()=="modello")
						modello=xmlparser.readElementText().toStdString();
					if(xmlparser.name()=="corde")
						corde=xmlparser.readElementText().toInt();
					if(xmlparser.name()=="prezzo")
						prezzo=xmlparser.readElementText().toDouble();
					if(xmlparser.name()=="amplificabile"){
						string stramp;
						stramp=xmlparser.readElementText().toStdString();
                        if(stramp=="1")
							amplf=true;
                        if(stramp=="0")
							amplf=false;
					}
					if(xmlparser.name()=="ponte")
						ponte=xmlparser.readElementText().toStdString();
					xmlparser.readNext();
				}
				acoustic* ac= new acoustic(modello,corde,prezzo,amplf,ponte);
				mag.push_back(ac);
			}
		}
    }
	}
    changed=false;//quando apro un file lo considero non modificato
}


void essemu::removeGtr(int i){
    delete mag[i];
    mag.deleteAt(i);
}

deque<guitar*> essemu::getAllGtr()const{
    return mag;
}

deque<int> essemu::searchgtrs(int cl, int cu, double pl, double pu, bool amp, string mo, string ponte, string typ, string pickup) const{
    deque<int> idx;
    if(typ==""){
        for(int i=0; i<mag.size(); ++i){
            electric* el=dynamic_cast<electric*>(mag[i]);
            if(
                    QString::fromStdString(mag[i]->get_name()).contains(QString::fromStdString(mo)) &&
                    mag[i]->get_corde()>=cl && mag[i]->get_corde()<=cu &&
                    mag[i]->get_price()>=pl && mag[i]->get_price()<=pu &&
                    mag[i]->amplf()>=amp &&
                    QString::fromStdString(mag[i]->get_ponte()).contains(QString::fromStdString(ponte)) &&
                    (
                        el &&
                        QString::fromStdString(el->get_pickup()).contains(QString::fromStdString(pickup))
                    )
               )
            {
                idx.push_back(i);
            }
        }
    }
    else if(typ=="electric"){
        for(int i=0; i<mag.size(); ++i){
            electric* el=dynamic_cast<electric*>(mag[i]);
            if(
                    el &&
                    QString::fromStdString(el->get_name()).contains(QString::fromStdString(mo)) &&
                    el->get_corde()>=cl && el->get_corde()<=cu &&
                    el->get_price()>=pl && el->get_price()<=pu
               )
            {
                idx.push_back(i);
            }
        }
    }
    else if(typ=="acoustic"){
        for(int i=0; i<mag.size(); ++i){
            acoustic* ac=dynamic_cast<acoustic*>(mag[i]);
            if(
                    ac &&
                    QString::fromStdString(ac->get_name()).contains(QString::fromStdString(mo)) &&
                    ac->get_corde()>=cl && ac->get_corde()<=cu &&
                    ac->get_price()>=pl && ac->get_price()<=pu &&
                    QString::fromStdString(ac->get_ponte()).contains(QString::fromStdString(ponte)) &&
                    ac->amplf()>=amp
               )
            {
                idx.push_back(i);
            }
        }
    }
    return idx;
}
