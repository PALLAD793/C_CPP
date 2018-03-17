#include "Menu.h"
#include "Administration.h"
#include "Operations.h"
#include <cstdlib>
#include <iostream>
//#include <conio.h>
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
    cout << "1. Add word" << endl;
    cout << "2. Remove word" << endl;
    cout << "3. Choose collection" << endl;
    cout << "4. Show union of collections" << endl;
    cout << "5. Show product of collections" << endl;
    cout << "6. Exit" << endl;

    while((opt1 = getch()))
    {

        switch(opt1)
        {
            case 49: addWord(); break;
            case 50: removeWord(); break;
            case 51: chooseCollection(); break;
            case 52: unionCollection(); break;
            case 53: productCollection(); break;
            case 54: return;
        }

        CLEAR

        cout << "What do you want to do?" << endl;
        cout << "1. Add word" << endl;
        cout << "2. Remove word" << endl;
        cout << "3. Choose collection" << endl;
        cout << "4. Show union of collections" << endl;
        cout << "5. Show product of collections" << endl;
        cout << "6. Exit" << endl;
    }

}

void Menu :: addWord()
{
    CLEAR
    string typedWord;

    cout << "Type word which you want add" << endl;
    cin >> typedWord;
    admin.addWord(typedWord);
}

void Menu :: removeWord()
{
    CLEAR

    string typedWord;

    cout << "Type word which you want remove" << endl;
    cin >> typedWord;
    admin.removeWord(typedWord);
}

void Menu :: chooseCollection()
{
    CLEAR

    int opt2;

    cout << "Choose collection which you want to see" << endl;
    cout << "1. Collection containing words with 5 letters and less" << endl;
    cout << "2. Collection containing words with 10 letters and more" << endl;
    cout << "3. Collection containing words with 15 letters and less" << endl;

    while((opt2 = getch()))
    {
        switch(opt2)
        {
            case 49: getMoreInfo((admin.lessThan5)); return;
            case 50: getMoreInfo((admin.moreThan10)); return;
            case 51: getMoreInfo((admin.lessThan15)); return;
        }
    }
}

void Menu :: getMoreInfo(Collection getMore)
{
    CLEAR

    int opt3;

    if(getMore.getAmountOfWords() != 0)
    {
        cout << "What do you want to do with chosen collection?" << endl;
        cout << "1. Show the longest word in collection" << endl;
        cout << "2. Show the shortest word in collection" << endl;
        cout << "3. Remove repeated words from collection" << endl;
        cout << "4. Sort collection alphabetically" << endl;
        cout << "5. Show words in collection" << endl;
        cout << "6. Go back to main menu" << endl;

        while((opt3 = getch()))
        {
            switch(opt3)
            {
                case 49: cout << getMore.showLongestWord() << endl; getch(); return;
                case 50: cout << getMore.showShortestWord() << endl; getch(); return;
                case 51: getMore.removeRepeatedWords(); cout << "Repeated words were removed" << endl; getch(); break;
                case 52: getMore.sortCollection(); cout << "Collection sorted" << endl; getch(); break;
                case 53: showWords(getMore); getch(); return;
                case 54: return;
            }

            CLEAR

            cout << "What do you want to do with chosen collection" << endl;
            cout << "1. Show the longest word in collection" << endl;
            cout << "2. Show the shortest word in collection" << endl;
            cout << "3. Remove repeated words from collection" << endl;
            cout << "4. Sort collection alphabetically" << endl;
            cout << "5. Show words in collection" << endl;
            cout << "6. Go back to main menu" << endl;
        }
    }
    else
    {
        cout << "Chosen collection is empty" << endl;
        getch();
    }

}

void Menu :: showWords(Collection getMoreInfo)
{
    int i, amountOfWords = getMoreInfo.getAmountOfWords();

    assert(amountOfWords>=0);

    for(i=0; i<amountOfWords; i++)
    {
        cout << getMoreInfo.getWord(i) << endl;
    }
}

void Menu :: unionCollection()
{
    CLEAR
    int choice1, choice2;

    cout << "Union of which collections do you want to do?" << endl;
    cout << "1. Collection containing words with 5 letters and less" << endl;
    cout << "2. Collection containing words with 10 letters and more" << endl;
    cout << "3. Collection containing words with 15 letters and less" << endl;
    cout << "Write two of them" << endl;
    cin >> choice1 >> choice2;
    while((choice1 != 1 && choice1 != 2 && choice1 != 3) || (choice2 != 1 && choice2 != 2 && choice2 != 3))
    {
        CLEAR
        cout << "Incorrect collections" << endl << endl;
        cout << "Union of which collections do you want to do?" << endl;
        cout << "1. Collection containing words with 5 letters and less" << endl;
        cout << "2. Collection containing words with 10 letters and more" << endl;
        cout << "3. Collection containing words with 15 letters and less" << endl;
        cout << "Write two of them" << endl;
        cin >> choice1 >> choice2;
    }

    if(choice1 == 1) compairFirst = admin.lessThan5;
    else if(choice1 == 2) compairFirst = admin.moreThan10;
    else compairFirst = admin.lessThan15;

    if(choice2 == 1) compairSecond = admin.lessThan5;
    else if(choice2 == 2) compairSecond = admin.moreThan10;
    else compairSecond = admin.lessThan15;

    cout << "Amount of words in new collection: " << operate.unionCollections(compairFirst.getAmountOfWords(), compairSecond.getAmountOfWords()) << endl;
    operate+compairFirst.collect;
    operate+compairSecond.collect;
    cout << "Words in new collection:" << endl;
    for(int i=0; i<operate.unionCollections(compairFirst.getAmountOfWords(), compairSecond.getAmountOfWords()); i++)
    {
        cout << operate.getUni(i) << endl;
    }
    operate.clearUni();
    getch();

}

void Menu :: productCollection()
{
    CLEAR
    int choice1, choice2;

    cout << "Product of which collections do you want to do?" << endl;
    cout << "1. Collection containing words with 5 letters and less" << endl;
    cout << "2. Collection containing words with 10 letters and more" << endl;
    cout << "3. Collection containing words with 15 letters and less" << endl;
    cout << "Write two of them" << endl;
    cin >> choice1 >> choice2;
    while((choice1 != 1 && choice1 != 2 && choice1 != 3) || (choice2 != 1 && choice2 != 2 && choice2 != 3))
    {
        CLEAR
        cout << "Incorrect collections" << endl << endl;
        cout << "Product of which collections do you want to do?" << endl;
        cout << "1. Collection containing words with 5 letters and less" << endl;
        cout << "2. Collection containing words with 10 letters and more" << endl;
        cout << "3. Collection containing words with 15 letters and less" << endl;
        cout << "Write two of them" << endl;
        cin >> choice1 >> choice2;
    }

    if(choice1 == 1) compairFirst = admin.lessThan5;
    else if(choice1 == 2) compairFirst = admin.moreThan10;
    else compairFirst = admin.lessThan15;

    if(choice2 == 1) compairSecond = admin.lessThan5;
    else if(choice2 == 2) compairSecond = admin.moreThan10;
    else compairSecond = admin.lessThan15;

    if((choice1 == 1 && choice2 == 2)||(choice1 ==2 && choice2 == 1))
    {
        cout << "Amount of words in new collection: 0"<< endl;
        cout << "No words in collection" << endl;
    }
    else
    {
        operate.productCollections(compairFirst, compairSecond);
        cout << "Amount of words in new collection: " << operate.getAmountProduct() << endl;
        cout << "Words in new collection:" << endl;
        for(int i = 0; i < operate.getAmountProduct(); i++)
        {
            cout << operate.getProduct(i) << endl;
        }
        operate.clearProduct();
    }

    getch();
}
