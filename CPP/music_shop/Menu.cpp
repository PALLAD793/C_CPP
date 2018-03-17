#include "Menu.h"

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <assert.h>



#ifdef _WIN32
    #define CLEAR system("cls");
    #include <conio.h>
#else
    #define CLEAR system("clear");
    #include <ncurses.h>
#endif // WIN32

using namespace std;

Menu :: Menu()
{
   option();
}


void Menu :: option()
{
    int opt1;

    cout << "What do you want to do?" << endl;
    cout << "1. Add client" << endl;
    cout << "2. Set a purchase order" << endl;
    cout << "3. Show clients" << endl;
    cout << "4. Show products" << endl;
    cout << "5. Make invoice" << endl;
    cout << "6. Show invoices" << endl;
    cout << "7. Exit" << endl;

    while((opt1 = getch()))
    {

        switch(opt1)
        {
            case 49: addClient(); break;
            case 50: purchaseOrder(); break;
            case 51: showClients(); getch(); break;
            case 52: showProducts(); getch(); break;
            case 53: makeInvoice(); break;
            case 54: showInvoices(); break;
            case 55: return;
        }

        CLEAR

        cout << "What do you want to do?" << endl;
        cout << "1. Add client" << endl;
        cout << "2. Set a purchase order" << endl;
        cout << "3. Show clients" << endl;
        cout << "4. Show products" << endl;
        cout << "5. Make invoice" << endl;
        cout << "6. Show invoices" << endl;
        cout << "7. Exit" << endl;
    }

}

void Menu :: addClient()
{
    Client *newClient;
    newClient = new Client;

    string pom;
    int num;

    CLEAR

    cout << "Type client's first name" << endl;
    cin >> pom;
    newClient->changeFirst(pom);

    CLEAR

    cout << "Type client's last name" << endl;
    cin >> pom;
    newClient->changeSecond(pom);

    CLEAR

    cout << "Type client's address of residence" << endl;
    cin >> pom;
    newClient->changeCity(pom);

    CLEAR

    cout << "Type client's street name" << endl;
    cin >> pom;
    newClient->changeStreet(pom);

    CLEAR

    cout << "Type client's residence number" << endl;
    cin >> num;
    newClient->changeNumber(num);

    CLEAR

    shop.addClient(newClient);
}

void Menu :: showOneClient(int i)
{
    cout << "Id: " << i << endl;
    cout << "First name: " << (shop.clients[i])->getFirst() << endl;
    cout << "Second name: " << (shop.clients[i])->getSecond() << endl;
    cout << "City: " << (shop.clients[i])->getCity() << endl;
    cout << "Street: " << (shop.clients[i])->getStreet() << " " << (shop.clients[i])->getNumber() << endl;
    cout << endl;
}

void Menu :: showClients()
{
    int numberClients;
    numberClients = shop.getAmountOfClients();

    CLEAR

    if(numberClients>0)
    {
        assert(numberClients>0);
        for(int i=0; i<numberClients; i++)
        {
            showOneClient(i);
        }
    }
    else cout << "No clients yet" << endl;
}

void Menu :: purchaseOrder()
{
    Supply *newSupply;
    newSupply = new Supply;

    CLEAR

    int opt2;

    cout << "What do you want to do?" << endl;
    cout << "1. Add product to order" << endl;
    cout << "2. Show products" << endl;
    cout << "3. Make an order" << endl;

    while((opt2 = getch()))
    {

        switch(opt2)
        {
            case 49: newSupply->addProductToSupply(addOrderProduct()); break;
            case 50: showOrderProducts(newSupply); break;
            case 51: shop.acceptSupply(newSupply); return;
        }

        CLEAR

        cout << "What do you want to do?" << endl;
        cout << "1. Add product to order" << endl;
        cout << "2. Show products" << endl;
        cout << "3. Make an order" << endl;
    }
}

Product* Menu :: addOrderProduct()
{
    Product *newProduct;
    newProduct = new Product;
    string pom;
    double cost;
    int amount;

    CLEAR

    cout << "Type product's name" << endl;
    cin >> pom;
    newProduct->changeType(pom);

    CLEAR

    cout << "Type product's brand" << endl;
    cin >> pom;
    newProduct->changeBrand(pom);

    CLEAR

    cout << "Type product's color" << endl;
    cin >> pom;
    newProduct->changeColor(pom);

    CLEAR

    cout << "Type product's price" << endl;
    cin >> cost;
    newProduct->changePrice(cost);

    CLEAR

    cout << "Type amount of products" << endl;
    cin >> amount;
    newProduct->changeAmount(amount);

    CLEAR

    return newProduct;
}

void Menu :: showOrderProducts(Supply* supply)
{
    int amount;
    amount = supply->getAmountOfProducts();

    CLEAR

    if(amount>0)
    {
        for(int i=0; i<amount; i++)
        {
            cout << "Id: " << i << endl;
            cout << "Name: " << supply->getType(i) << endl;
            cout << "Brand: " << supply->getBrand(i) << endl;
            cout << "Color: " << supply->getColor(i) << endl;
            cout << "Price: " << supply->getPrice(i) << endl;
            cout << "Amount: " << supply->getAmount(i) << endl << endl;
        }
    }
    else cout << "No products yet" << endl;

    getch();
}

void Menu :: showOneProduct(int i)
{
    cout << "Id: " << i << endl;
    cout << "Name: " << shop.getType(i) << endl;
    cout << "Brand: " << shop.getBrand(i) << endl;
    cout << "Color: " << shop.getColor(i) << endl;
    cout << "Price: " << shop.getPrice(i) << endl;
    cout << "Amount: " << shop.getAmount(i) << endl << endl;
}

void Menu :: showProducts()
{
    int amount;
    amount = shop.getAmountOfProducts();

    CLEAR

    if(amount>0)
    {
        for(int i=0; i<amount; i++)
        {
            showOneProduct(i);
        }
    }
    else cout << "No products yet" << endl;
}

void Menu :: makeInvoice()
{
    Invoice* newInvoice;
    newInvoice = new Invoice;

    CLEAR

    int opt3;

    cout << "What do you want to do?" << endl;
    cout << "1. Choose customer" << endl;
    cout << "2. Choose product" << endl;
    cout << "3. Save and close invoice" << endl;

    while((opt3 = getch()))
    {

        switch(opt3)
        {
            case 49: Client* client2; client2 = chooseCustomer(); if(client2 !=0) newInvoice->addClient(client2); break;
            case 50: Product* product2; product2 = buy(newInvoice); if(product2 != 0) newInvoice->addProductToSupply(product2); break;
            case 51: if(newInvoice->getAmountOfProducts()>0) saveInvoice(newInvoice); return;
        }

        CLEAR

        cout << "What do you want to do?" << endl;
        cout << "1. Choose customer" << endl;
        cout << "2. Choose product" << endl;
        cout << "3. Save and close invoice" << endl;
    }
}

Client* Menu :: chooseCustomer()
{
    CLEAR

    showClients();

    if(shop.getAmountOfClients()>0)
    {
        int id;
        cout << "Type customer's Id" << endl;
        cin >> id;
        if(id<shop.getAmountOfClients() && id>=0)
            return shop.clients[id];
        else
        {
            CLEAR
            cout << "Not recognized Id" << endl;
            getch();
            return 0;
        }

    }
    getch();
    return 0;
}

Product* Menu :: chooseProduct()
{
    CLEAR

    showProducts();

    if(shop.getAmountOfProducts()>0)
    {
        int idp;
        cout << "Type product's Id" << endl;
        cin >> idp;
        if(idp<shop.getAmountOfProducts() && idp>=0)
            return shop.getProductFromSupply(idp);
        else
        {
            CLEAR
            cout << "Not recognized Id" << endl;
            getch();
            return 0;
        }
    }
    getch();
}

Product* Menu :: buy(Invoice* newInvoice)
{
    Product* product;
    product = chooseProduct();

    CLEAR

    if(shop.getAmountOfProducts()>0 && product != 0)
    {
        int amount;

        while(amount<0 || amount > product->getAmount())
        {
            CLEAR
            cout << "How many features?" << endl;
            cout << "There is " << product->getAmount() << " in our magazine" << endl;
            cin >> amount;
        }

        return newInvoice->buyProduct(product, amount);
    }
    return 0;
}

void Menu :: saveInvoice(Invoice* invoice)
{
    shop.addInvoice(invoice);
}

void Menu :: showOneInvoice(int i)
{

    cout << "Number Id: " << i << endl << endl;
    cout << "Customer's details" << endl;
    cout << "First name: " << shop.invoices[i]->getFirst() << endl;
    cout << "Last name: " << shop.invoices[i]->getSecond() << endl;
    cout << "City: " << shop.invoices[i]->getCity() << " " << shop.invoices[i]->getNumber() << endl << endl;

    int amount;
    amount = shop.invoices[i]->getAmountOfProducts();

    if(amount>0)
    {
        cout << "Bought features" << endl;

        for(int j=0; j<amount; j++)
        {
            cout << shop.invoices[i]->getType(j) <<  "\t" << shop.invoices[i]->getBrand(j) << "\t" << shop.invoices[i]->getColor(j) << "\t" << shop.invoices[i]->getAmount(j) << "\t" << shop.invoices[i]->getPrice(j) << " zl" << endl;
        }

        cout << endl << "Total cost: " << shop.invoices[i]->countSum() << " zl" << endl << endl;
    }
    else cout << "Nothing bought" << endl;
    cout << "--------------------------" << endl << endl;
}

void Menu :: showInvoices()
{
    CLEAR

    if(shop.getAmountOfInvoices()>0)
    {
        for(int i=0; i<shop.getAmountOfInvoices(); i++)
        {
            showOneInvoice(i);
        }
    }
    else cout << "There's no invoices";

    getch();
}
