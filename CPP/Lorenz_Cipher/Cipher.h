#ifndef CIPHER_H
#define CIPHER_H

#include "Rotor.h"
#include <string>


class Cipher
{
    int tab1[32] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' ',',','-','.','!','*'};
    std::string tab2[32] = {"00011","11001","01110","01001","00001","01101","11010","10100","00110","01011","01111","10010","11100","01100","11000","10110","10111","01010","00101","10000",
    "00111","11110","10011","11101","10101","10001","00100","01000","00010","11111","11011","00000"};
    std::string outText="", temp1="", temp2="";
    void xorKWheel(char x);
    std::string xorSWheel(std::string x);
    void moveKWheels();
    void moveSWheels();
    void decryptBits(std::string x);
public:
    Rotor<bool, 52> wheelK[5];
    Rotor<bool, 44> wheelM;
    Rotor<bool, 35> wheelS[5];

    void encrypt(std::string inText);
    std::string encryptedText();
};


#endif // CIPHER_H
