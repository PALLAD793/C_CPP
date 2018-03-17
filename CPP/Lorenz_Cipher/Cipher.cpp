#include "Cipher.h"
#include "Rotor.h"

#include <iostream>
#include <string.h>


void Cipher :: encrypt(std::string inText)
{
    outText ="";
    for(int i=0; i<inText.length(); i++)
    {
        temp1="", temp2="";
        xorKWheel(inText[i]);
        moveKWheels();
        temp2 = xorSWheel(temp1);
        moveSWheels();
        decryptBits(temp2);
    }
}

void Cipher :: decryptBits(std::string temp2)
{
    int i=0;

    while(tab2[i] != temp2) i++;

    outText += tab1[i];
}

void Cipher :: xorKWheel(char x)
{
    int i=0;
    std::string bits="", xbits="";
    while(tab1[i] != x && i<32) i++;
    if(i<32)
    {
        bits = tab2[i];

        for(int j=0; j<5; j++)
        {
            xbits += ((bits[j]-48) ^ (wheelK[j].getBit()-208));
        }
        temp1 = xbits;
    }
}

std::string Cipher :: xorSWheel(std::string temp1)
{
    std::string xbits="";

    for(int i=0; i<5; i++)
    {
        xbits += ((temp1[i]-48) ^ (wheelS[i].getBit()-208));
    }
    return xbits;
}

void Cipher :: moveKWheels()
{
    for(int i=0; i<5; i++)
    {
        wheelK[i].moveRotor();
    }
}

void Cipher :: moveSWheels()
{
    for(int j=0; j<5; j++)
    {
        if(wheelM.getBit() == 1)
        {
            wheelS[j].moveRotor();
        }

        wheelM.moveRotor();
    }
}

std::string Cipher :: encryptedText()
{
    return outText;
}
