#include "Invoice.h"

Product* Invoice :: buyProduct(Product* product, int amount)
{
    Product* feature;
    feature = new Product;

    feature->changeType(product->getType());
    feature->changeBrand(product->getBrand());
    feature->changeColor(product->getColor());
    feature->changePrice(product->getPrice());
    feature->changeAmount(amount);

    product->changeAmount(product->getAmount()-amount);

    return feature;
}

void Invoice :: addClient(Client* client)
{
    firstName = client->getFirst();
    lastName = client->getSecond();
    city = client->getCity();
    street = client->getStreet();
    number = client->getNumber();
}

double Invoice :: countSum()
{
    sum = 0;
    for(int i=0; i<getAmountOfProducts(); i++) sum+= (productSupply[i]->getAmount() * productSupply[i]->getPrice());

    return sum;
}
