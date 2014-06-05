#include "acoustic.h"

acoustic::~acoustic(){}

acoustic::acoustic(string nm,int cr, double prc, bool amp, string pnt): guitar(nm,cr,prc), amplificazione(amp), ponte(pnt) {}

acoustic::acoustic(const acoustic& ac): guitar(ac), amplificazione(ac.amplificazione), ponte(ac.ponte) {}

acoustic& acoustic::operator=(const acoustic& ac){
	guitar::operator=(ac);
	amplificazione=ac.amplificazione;
	return *this;
}

bool acoustic::operator==(const guitar& gtr)const{
	const acoustic* ac = dynamic_cast<const acoustic*>(&gtr);
	return ac && (*this).guitar::operator==(gtr) && amplificazione==(*ac).amplificazione && ponte==(*ac).ponte;
}

bool acoustic::amplf() const{
	return amplificazione;
}

void acoustic::set_amplf(bool e){
	amplificazione=e;
}

void acoustic::set_ponte(string st){
	ponte=st;
}

string acoustic::get_ponte()const{
	return ponte;
}
