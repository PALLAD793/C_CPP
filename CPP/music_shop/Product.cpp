#include "Product.h"

double Product :: changePrice(double pr)
{
    int x = pr*100;
    price = (double)x/100;
    return price;
}

std::string Product :: changeColor(std::string co)
{
    color = co;
    return color;
}

std::string Product :: changeBrand(std::string br)
{
    brand = br;
    return brand;
}

std::string Product :: changeType(std::string ty)
{
    type = ty;
    return type;
}

double Product :: getPrice()
{
    return price;
}

std::string Product :: getColor()
{
    return color;
}

std::string Product :: getBrand()
{
    return brand;
}

std::string Product :: getType()
{
    return type;
}

int Product :: changeAmount(int am)
{
    amount = am;
    return amount;
}

int Product :: getAmount()
{
    return amount;
}
