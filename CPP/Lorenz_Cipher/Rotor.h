#ifndef ROTOR_H
#define ROTOR_H

#include <cstdio>
#include <cstdlib>
#include <string>

template <typename T1, int T2>
class Rotor
{
    struct Sprocket
    {
        int id;
        T1 bit;
        Sprocket* next;

        Sprocket(int x, T1 value)
        {
            id = x;
            bit = value;
        }
    };

    Sprocket* head=NULL;
    Sprocket* curPos=head;


    void addSprocket(int id, T1 value);
public:
    Rotor();

    std::string pom="";
    int getIdC();
    T1 getBit();
    void makeWheel(int amount);
    void changeHead(int idH);
    void moveRotor();
    void resetCurPos();

};

template <typename T1, int T2>
Rotor<T1,T2> :: Rotor()
{
    makeWheel(T2);
}


template <typename T1, int T2>
void Rotor<T1,T2> :: makeWheel(int amount)
{
    for(int i=0; i<amount; i++)
    {
        T1 x = (std::rand()%2);
        addSprocket(i, x);
    }
    curPos = head;
}

template <typename T1, int T2>
void Rotor<T1,T2> :: addSprocket(int id, T1 value)
{
    if(head != NULL)
    {
        Sprocket* temp = head;
        Sprocket* create;
        while(temp->next != head)
        {
            temp = temp->next;
        }

        create = new Sprocket(id, value);
        create->next = head;
        temp->next = create;
    }
    else
    {
        head = new Sprocket(id, value);
        head->next = head;
    }
}

template <typename T1, int T2>
void Rotor<T1,T2> :: changeHead(int idH)
{
    Sprocket* temp = head;
    while(temp->id != idH)
    {
        temp = temp->next;
    }
    head = temp;
    curPos = temp;
}

template <typename T1, int T2>
int Rotor<T1,T2> :: getIdC()
{
   return curPos->id;
}

template <typename T1, int T2>
T1 Rotor<T1,T2> :: getBit()
{
    return curPos->bit;
}

template <typename T1, int T2>
void Rotor<T1,T2> :: moveRotor()
{
    curPos = curPos->next;
}

template <typename T1, int T2>
void Rotor<T1,T2> :: resetCurPos()
{
    curPos = head;
}

#endif
