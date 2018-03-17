#ifndef ADMINISTRATION_H
#define ADMINISTRATION_H
#include "Collection.h"
#include <string>

using namespace std;

class Administration
{
    Collection lessThan5, lessThan15, moreThan10;
    friend class Menu;
public:

    void addWord(string word);
    void removeWord(string word);
};

#endif // ADMINISTRATION_H

