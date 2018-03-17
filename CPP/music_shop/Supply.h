#ifndef SUPPLY_H
#define SUPPLY_H

#include "Product.h"
#include <vector>

class Supply
{
protected:
    std::vector <Product*> productSupply;

public:
    int getAmountOfProducts();
    Product* addProductToSupply(Product* product);
    Product* getProductFromSupply(int num);
    std::string getType(int num);
    std::string getBrand(int num);
    std::string getColor(int num);
    double getPrice(int num);
    int getAmount(int num);
};

#endif // SUPPLY_H
