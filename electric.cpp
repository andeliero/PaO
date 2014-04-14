#include "electric.h"

electric::~electric(){}

electric::electric(string nm, int cr, double prc, string pnt, string pk): guitar(nm,cr,prc), ponte(pnt), pickup(pk){}

electric::electric(const electric& elt): guitar(elt), ponte(elt.ponte), pickup(elt.pickup) {}

electric& electric::operator=(const electric& elt){
	guitar::operator=(elt);
	ponte=elt.ponte;
	pickup=elt.pickup;
	return *this;
}

bool electric::operator==(const guitar& gtr)const{
	const electric* elt=dynamic_cast<const electric*>(&gtr);
	return elt && (*this).guitar::operator==(gtr) && ponte==(*elt).ponte && pickup==(*elt).pickup;
}

bool electric::amplf() const{
	return true;
}

string electric::get_ponte()const{
	return ponte;
}

void electric::set_ponte(string pnt){
	ponte=pnt;
}

string electric::get_pickup()const{
	return pickup;
}

void electric::set_pickup(string pkp){
	pickup=pkp;
}