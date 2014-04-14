#ifndef GUITAR_H
#define GUITAR_H 
#include <string>
using std::string;

class guitar{
private:
	string modello;//nome del modello
	int corde;//o modello 6 corde o 12 corde
	double price;//prezzo di listino
protected:
	guitar(string,int,double);
	guitar(const guitar&);
	guitar& operator=(const guitar&);
public:
	virtual ~guitar();
	virtual bool operator==(const guitar&)const;
	string get_name()const;
	void set_name(string);
	int get_corde()const;
	void set_corde(int);
	double get_price()const;
	void set_price(double);
	virtual bool amplf() const =0;
};

#endif