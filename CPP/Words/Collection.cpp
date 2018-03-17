#include "Collection.h"
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

void Collection :: addWord(string word)
{
    collect.push_back(word);
}

void Collection :: removeWord(string word)
{
    unsigned int i=0;

    while(i < collect.size() && !(collect[i] == word)) i++;

    if(i<collect.size()) collect.erase(collect.begin()+i);
}

void Collection :: removeRepeatedWords()
{
    sort(collect.begin(), collect.end());
    unsigned int i=0;

    while(i < collect.size()-1)
    {
        unsigned j=i+1;
        while(collect[i] == collect[j])
        {
            collect.erase(collect.begin()+j);
        }
        i++;
    }

}

void Collection :: sortCollection()
{
    sort(collect.begin(), collect.end());
}

int Collection :: getAmountOfWords()
{
   return collect.size();
}

string Collection :: getWord(int i)
{
    return collect[i];
}

string Collection :: showLongestWord()
{
    unsigned int i, maxLength=0, idWord=0;
    for(i=0; i< collect.size(); i++)
    {
        if(maxLength<collect[i].length())
        {
            maxLength = collect[i].length();
            idWord = i;
        }
    }

    return collect[idWord];
}

string Collection :: showShortestWord()
{
    unsigned int i, minLength=999, idWord=0;
    for(i=0; i<collect.size(); i++)
    {
        if(minLength > collect[i].length())
        {
            minLength = collect[i].length();
            idWord = i;
        }
    }

    return collect[idWord];
}
