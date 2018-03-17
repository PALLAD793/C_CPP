#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product
{
public:

    double changePrice(double pr);
    double getPrice();
    std::string changeBrand(std::string br);
    std::string changeColor(std::string co);
    std::string changeType(std::string ty);
    std::string getBrand();
    std::string getColor();
    std::string getType();
    int changeAmount(int am);
    int getAmount();
private:
    double price=0;
    std::string color="", brand="", type="";
    int amount=0;
};



#endif // PRODUCT_H
