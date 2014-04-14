#include "acoustic.h"

acoustic::~acoustic(){}

acoustic::acoustic(string nm,int cr, double prc, bool amp): guitar(nm,cr,prc), amplificazione(amp) {}

acoustic::acoustic(const acoustic& ac): guitar(ac), amplificazione(ac.amplificazione) {}

acoustic& acoustic::operator=(const acoustic& ac){
	guitar::operator=(ac);
	amplificazione=ac.amplificazione;
	return *this;
}

bool acoustic::operator==(const guitar& gtr)const{
	const acoustic* ac = dynamic_cast<const acoustic*>(&gtr);
	return ac && (*this).guitar::operator==(gtr) && amplificazione==(*ac).amplificazione;
}

bool acoustic::amplf() const{
	return amplificazione;
}