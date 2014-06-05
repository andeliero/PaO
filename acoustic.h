#ifndef ACOUSTIC_H
#define ACOUSTIC_H
#include "guitar.h" 
#include <string>
using std::string;

class acoustic: public guitar{
private:
	bool amplificazione;//se provvisto di amplificazione
	string ponte;
public:
	~acoustic();
	acoustic(string,int,double,bool,string);
	acoustic(const acoustic&);
	acoustic& operator=(const acoustic&);
	/*virtual*/ bool operator==(const guitar&)const;
	/*virtual*/ bool amplf()const;
	void set_amplf(bool);
	void set_ponte(string);
	string get_ponte()const;
};

#endif