#ifndef MENU_H
#define MENU_H

#include <string>
#include "Shop.h"
#include "Client.h"
#include "Supply.h"
#include "Invoice.h"

class Menu
{

    void addClient();
    void showOneClient(int i);
    void showClients();
    void option();
    void purchaseOrder();
    Product* addOrderProduct();
    void showOrderProducts(Supply* supply);
    void showOneProduct(int i);
    void showProducts();
    void makeInvoice();
    Client* chooseCustomer();
    Product* chooseProduct();
    Product* buy(Invoice* newInvoice);
    void saveInvoice(Invoice* invoice);
    void showOneInvoice(int i);
    void showInvoices();

public:
    Shop shop;
    Menu();
};
#endif // MENU_H
