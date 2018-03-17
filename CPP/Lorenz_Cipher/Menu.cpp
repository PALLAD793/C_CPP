#include "Menu.h"
#include "Rotor.h"
#include "Cipher.h"

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <assert.h>
#include <fstream>


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
    cout << "1. Console" << endl;
    cout << "2. File" << endl;
    cout << "3. Exit" << endl;

    while((opt1 = getch()))
    {

        switch(opt1)
        {
            case 49: optConsole(); break;
            case 50: optFile(); break;
            case 51: return;
        }

        CLEAR

        cout << "What do you want to do?" << endl;
        cout << "1. Console" << endl;
        cout << "2. File" << endl;
        cout << "3. Exit" << endl;
    }

}

void Menu :: optConsole()
{
    CLEAR

    int opt2;


    cout << "What do you want to do?" << endl;
    cout << "1. Load text on which you want operate" << endl;
    cout << "2. Show loaded text" << endl;
    cout << "3. Remove loaded text" << endl;
    cout << "4. Set key" << endl;
    cout << "5. Show key" << endl;
    cout << "6. Encrypt/Decrypt loaded text" << endl;


    while((opt2 = getch()))
    {
        switch(opt2)
        {
            case 49: getText(opText); return;
            case 50: showText(); return;
            case 51: removeText(); return;
            case 52: setKey(); return;
            case 53: getKey(); return;
            case 54: cout << encryptText(opText); getch(); return;
        }
    }
}

void Menu :: optFile()
{
    CLEAR

    int opt3;

    ofstream fileOut("TextEncrypted.txt");

    cout << "What do you want to do?" << endl;
    cout << "1. Load text on which you want operate" << endl;
    cout << "2. Show loaded text" << endl;
    cout << "3. Remove loaded text" << endl;
    cout << "4. Set key" << endl;
    cout << "5. Show key" << endl;
    cout << "6. Encrypt/Decrypt loaded text" << endl;

    while((opt3 = getch()))
    {
        switch(opt3)
        {
            case 49: getTextFile(opText); return;
            case 50: showText(); return;
            case 51: removeText(); return;
            case 52: setKey(); return;
            case 53: getKey(); return;
            case 54: fileOut << encryptText(opText); getch(); return;
        }
    }

}

void Menu :: getText(string & opText)
{
    string loText;
    cout << "Write your text" << endl;
    getline(cin, loText);
    opText += loText;
}

void Menu :: getTextFile(string &opText)
{
    opText = "";
    fstream fileIn("TextToEncrypt.txt", ios::in);
    if( fileIn.good() == true )
    {
        string loText;
        while(!fileIn.eof())
        {
            getline(fileIn, loText);
            opText += loText;
        }
        cout << "Done" << endl;
    }
    else cout << "Permission denied" << endl;

    getch();

    fileIn.close();
}

void Menu :: showText()
{
    if(opText.length() == 0) cout << "Text not loaded" << endl;
    else cout << opText << endl;

    getch();
}

void Menu :: removeText()
{
    opText = "";
    assert(opText.length() == 0);
}

void Menu :: setKey()
{

    cout << "Where do you want to start? (wheels: K1, K2, K3, K4, K5, M, S1, S2, S3, S4, S5)" << endl;
    int key[11];
    for(int i=0; i<11; i++)
    {
        cin >> key[i];
    }

    for(int i=0; i<5; i++)
    {
        cipher.wheelK[i].changeHead(key[i]);
    }

    cipher.wheelM.changeHead(key[5]);

    for(int i=0; i<5; i++)
    {
        cipher.wheelS[i].changeHead(key[i+6]);
    }
}

void Menu :: getKey()
{
    cout << "Set key:" << endl;

    for(int i=0; i<5; i++)
    {
        cout << cipher.wheelK[i].getIdC() << " ";
    }
    cout << cipher.wheelM.getIdC() << " ";
    for(int i=0; i<5; i++)
    {
        cout << cipher.wheelS[i].getIdC() << " ";
    }
    cout << endl;
    getch();
}

std::string Menu :: encryptText(std::string opText)
{
    cipher.encrypt(opText);
    return cipher.encryptedText();
}

