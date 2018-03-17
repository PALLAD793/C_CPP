#ifndef MENU_H
#define MENU_H
#include "Administration.h"
#include "Operations.h"
#include "Tests.h"


class Menu
{
    Collection compairFirst, compairSecond;
    Operations operate;
    Tests tests;

    void addWord();             //add word to all appropriate collections
    void removeWord();          //remove word from all collections
    void chooseCollection();
    void getMoreInfo(Collection getMore);         //shows the longest and the shortest word in chosen collection, sort words in collection and show them
    void option();              //main menu
    void showWords(Collection getMoreInfo);
    void unionCollection();
    void productCollection();

public:
    Administration admin;
    Menu();
};
#endif // MENU_H
