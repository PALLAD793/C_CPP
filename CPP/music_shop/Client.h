#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client
{
public:
    std::string firstName="", lastName="", city="", street="";
    int number=0;

    std::string changeFirst(std::string name);
    std::string changeSecond(std::string second);
    std::string changeCity(std::string ci);
    std::string changeStreet(std::string str);
    std::string getFirst();
    std::string getSecond();
    std::string getCity();
    std::string getStreet();
    int changeNumber(int num);
    int getNumber();
};
#endif // CLIENT_H
