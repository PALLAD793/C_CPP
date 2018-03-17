#ifndef MENU_H
#define MENU_H

#include <string>
#include "Rotor.h"
#include "Cipher.h"

class Menu
{

    std::string opText ="", enText="";
    void optConsole();
    void optFile();
    void option();
    void getText(std::string &opText);
    void setKey();
    void getKey();
    void removeText();
    void showText();
    void getTextFile(std::string &opText);
    std::string encryptText(std::string opText);


public:
    Cipher cipher;
    Menu();
};
#endif // MENU_H
