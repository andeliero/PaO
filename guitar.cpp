#include "guitar.h"

guitar::~guitar(){}

guitar::guitar(string nm,int cr,double prc): modello(nm), corde(cr), price(prc){}

guitar::guitar(const guitar& gtr): modello(gtr.modello), corde(gtr.corde), price(gtr.price) {}

guitar& guitar::operator=(const guitar& gtr){
	modello=gtr.modello;
	corde=gtr.corde;
	price=gtr.price;
	return *this;
}

bool guitar::operator==(const guitar& gtr)const{
	return modello==gtr.modello && corde==gtr.corde && price==gtr.price;
}

string guitar::get_name()const{
	return modello;
}

void guitar::set_name(string a){
	modello=a;
}

int guitar::get_corde()const{
	return corde;
}

void guitar::set_corde(int a){
	corde=a;
}

double guitar::get_price()const{
	return price;
}

void guitar::set_price(double a){
	price=a;
}
