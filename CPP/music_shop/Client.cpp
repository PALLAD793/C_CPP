#include "Client.h"

std::string Client :: changeFirst(std::string name)
{
    firstName = name;
    return firstName;
}

std::string Client :: changeSecond(std::string second)
{
    lastName = second;
    return lastName;
}

std::string Client :: changeCity(std::string ci)
{
    city = ci;
    return city;
}

std::string Client :: changeStreet(std::string str)
{
    street = str;
    return street;
}

std::string Client :: getFirst()
{
    return firstName;
}

std::string Client :: getSecond()
{
    return lastName;
}

std::string Client :: getCity()
{
    return city;
}

std::string Client :: getStreet()
{
    return street;
}

int Client :: changeNumber(int num)
{
    number = num;
    return number;
}

int Client :: getNumber()
{
    return number;
}
