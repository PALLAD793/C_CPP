#ifndef OPERATIONS_H
#define OPERATIONS_H
#include "Collection.h"

class Operations
{
    vector <string> product, uni;
public:
    void productCollections(Collection first, Collection second);
    int unionCollections(int firstVectorLength, int secondVectorLength);
    void clearProduct();
    void clearUni();
    int getAmountProduct();
    void operator+(const vector <string> first);
    string getUni(int i);
    string getProduct(int i);
};
#endif // OPERATIONS_H
