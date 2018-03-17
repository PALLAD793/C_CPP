#ifndef SHOP_H
#define SHOP_H

#include "Client.h"
#include "Supply.h"
#include "Invoice.h"
#include <vector>

class Shop: public Supply
{

public:
    std::vector <Client*> clients;
    std::vector <Invoice*> invoices;
    void addClient(Client* client);
    void addInvoice(Invoice* invoice);
    void acceptSupply(Supply* supply);
    int getAmountOfClients();
    int getAmountOfInvoices();

};
#endif // SHOP_H
