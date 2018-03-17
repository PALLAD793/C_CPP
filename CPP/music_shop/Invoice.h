#ifndef INVOICE_H
#define INVOICE_H

#include "Client.h"
#include "Product.h"
#include "Supply.h"

class Invoice: public Supply, public Client
{
    double sum=0;
public:
    void addClient(Client* client);
    Product* buyProduct(Product* product, int amount);
    double countSum();
};
#endif // INVOICE_H

