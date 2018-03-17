#include "Supply.h"

int Supply :: getAmountOfProducts()
{
    return productSupply.size();
}

Product* Supply :: addProductToSupply(Product* product)
{
    productSupply.push_back(product);
    return productSupply[productSupply.size()-1];
}

Product* Supply :: getProductFromSupply(int num)
{
    return productSupply[num];
}

std::string Supply :: getType(int num)
{
    return productSupply[num]->getType();
}

std::string Supply :: getBrand(int num)
{
    return productSupply[num]->getBrand();
}

std::string Supply :: getColor(int num)
{
    return productSupply[num]->getColor();
}

double Supply :: getPrice(int num)
{
    return productSupply[num]->getPrice();
}

int Supply :: getAmount(int num)
{
    return productSupply[num]->getAmount();
}
