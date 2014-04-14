#ifndef ACOUSTIC_H
#define ACOUSTIC_H
#include "guitar.h" 
#include <string>
using std::string;

class acoustic: public guitar{
private:
	bool amplificazione;//se provvisto di amplificazione
public:
	~acoustic();
	acoustic(string,int,double,bool);
	acoustic(const acoustic&);
	acoustic& operator=(const acoustic&);
	/*virtual*/ bool operator==(const guitar&)const;
	/*virtual*/ bool amplf()const;
};

#endif