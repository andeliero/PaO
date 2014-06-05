#ifndef ESSEMU_H
#define ESSEMU_H
#include "deque.h"
#include "guitar.h"
#include "electric.h"
#include "acoustic.h"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QString>
#include <QFile>
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

class essemu{
private:
	deque<guitar*> mag;
    string file;//path del file
    bool changed;//variabile che indica se il magazzino è stato modificato dopo un salvataggio

public:
	essemu();
	~essemu();
    void deleteAll();
    bool isEmpty() const;
    string getFilename() const;
    bool isChanged() const;
    void setChanged(bool);
    void saveXml(string);
    void openXml(string);
    void insertGtr(const guitar&);//aggiunge in coda
    void removeGtr(int i);//int per indicare l'indice di posizionamento
	guitar* getGtr(int) const;
    void replaceGtr(guitar*,guitar*);
	deque<guitar*> getAllGtr()const;
    deque<int> searchgtrs(int cl,int cu,double pl,double pu, bool amp,string mo="",string ponte="",string typ="",string pickup="")const;
};

#endif
