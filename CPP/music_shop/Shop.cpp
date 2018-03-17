#include "Shop.h"

void Shop :: addClient(Client* client)
{
    clients.push_back(client);
}

int Shop :: getAmountOfClients()
{
    return clients.size();
}

void Shop :: acceptSupply(Supply* supply)
{
    int amount;
    amount = supply->getAmountOfProducts();
    for(int i=0; i<amount; i++)
    {
        productSupply.push_back(supply->getProductFromSupply(i));
    }
}

void Shop :: addInvoice(Invoice* invoice)
{
    invoices.push_back(invoice);
}

int Shop :: getAmountOfInvoices()
{
    return invoices.size();
}
