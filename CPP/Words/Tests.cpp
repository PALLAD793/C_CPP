#include "Tests.h"
#include "Collection.h"
#include "Operations.h"
#include "Administration.h"

Tests :: Tests()
{
    test1();
    test2();
}

void Tests :: test1()
{
    Collection collect;
    assert(collect.getAmountOfWords()==0);
}

void Tests :: test2()
{
    Operations operate;
    assert(operate.getAmountProduct()==0);
}
