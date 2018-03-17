#include "Administration.h"

using namespace std;

void Administration :: addWord(string word)
{

    if(word.length() <= 5)
    {
        lessThan5.addWord(word);
    }

    if(word.length() >= 10)
    {
        moreThan10.addWord(word);
    }

    if(word.length() <= 15)
    {
        lessThan15.addWord(word);
    }
}

void Administration :: removeWord(string word)
{
    if(word.length() <= 5 && lessThan5.getAmountOfWords() > 0)
    {
        lessThan5.removeWord(word);
    }

    if(word.length() >= 10 && moreThan10.getAmountOfWords() > 0)
    {
        moreThan10.removeWord(word);
    }

    if(word.length() <= 15 && lessThan15.getAmountOfWords() > 0)
    {
        lessThan15.removeWord(word);
    }
}


