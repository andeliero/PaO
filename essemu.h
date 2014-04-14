#ifndef ESSEMU_H
#define ESSEMU_H
#include "deque.h"
#include "guitar.h"
#include "electric.h"
#include "acoustic.h"
#include <QString>
#include <iostream>
using std::cout;
using std::endl;

class essemu{
private:
	deque<guitar*> mag;
public:
	essemu();
	~essemu();
	void saveXml(QString);
	void openXml(QString);
	void insertGtr(guitar*);
	void removeGtr(const guitar&);
	guitar* getGtr(int) const;
	void changeGtr(int pos,int tp);
	void sortbyName();
	deque<guitar*> getAllGtr()const;
};

#endif