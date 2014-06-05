#ifndef ELECTRIC_H
#define ELECTRIC_H 
#include "guitar.h"
#include <string>
using std::string;

class electric: public guitar {
private:
	string ponte;//nome del ponte
	string pickup;//nome modello dei pick up
public:
	~electric();
	electric(string,int,double,string,string);
	electric(const electric&);
	electric& operator=(const electric&);
	/*virtual*/ bool operator==(const guitar&)const;
	/*virtual*/ bool amplf()const;
	string get_ponte()const;
	void set_ponte(string);
	string get_pickup()const;
	void set_pickup(string);
};

#endif