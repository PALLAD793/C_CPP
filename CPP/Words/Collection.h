#ifndef COLLECTION_H
#define COLLECTION_H
#include <vector>
#include <string>

using namespace std;

class Collection
{
    vector <string> collect;
    friend class Operations;
    friend class Administration;
    friend class Menu;
public:

    void addWord(string word);
    void removeWord(string word);
    void removeRepeatedWords();
    void sortCollection();
    int getAmountOfWords();
    string getWord(int i);
    string showLongestWord();
    string showShortestWord();
};

#endif // COLLECTION_H
