#include "Operations.h"
#include <algorithm>

void Operations :: productCollections(Collection first, Collection second)
{
    sort(first.collect.begin(), first.collect.end());
    sort(second.collect.begin(), second.collect.end());
    unsigned int i=0;
    while(i < first.collect.size())
    {
        unsigned int j=0;
        while(j < second.collect.size() && first.collect[i] != second.collect[j]) j++;

        if(first.collect[i] == second.collect[j])
        {
            product.push_back(first.collect[i]);
        }
        i++;
    }
}

void Operations :: operator+(const vector <string> first)
{
    for(int i=0; i<first.size(); i++)
    {
        uni.push_back(first[i]);
    }
}
int Operations :: unionCollections(int firstVectorLength, int secondVectorLength)
{
    return (firstVectorLength+secondVectorLength);
}

void Operations :: clearProduct()
{
    product.clear();
}

void Operations :: clearUni()
{
    uni.clear();
}

int Operations :: getAmountProduct()
{
    return product.size();
}


string Operations :: getProduct(int i)
{
    return product[i];
}

string Operations :: getUni(int i)
{
    return uni[i];
}
