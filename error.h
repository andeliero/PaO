#ifndef ERROR_H
#define ERROR_H
#include <string>
using std::string;

//errori per la classe deque

class OutIndex{};

//--------------------------

class error{
private:
    string msg;
public:
    error(string a){
        msg=a;
    }
    string getMsg() const{
        return msg;
    }
};

#endif // ERROR_H
