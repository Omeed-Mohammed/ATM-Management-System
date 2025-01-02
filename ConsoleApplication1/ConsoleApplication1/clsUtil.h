#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include "clsDate.h"
#include <cstdlib>
using namespace std;
class clsUtil
{
protected:


public:
    static void Srand()
    {
        srand((unsigned)time(NULL));
    }

    static int RandomNumber(int From, int To)
    {
        //Function to generate a random number

        int RanNum = rand() % (To - From + 1) + From;
        return RanNum;
    }

    //*********************************************************
    //Random Caracter

    enum enCharType {
        SmallLetter = 1, CapitalLetter = 2,
        Digit = 3, SpecialCharacter = 4, MixChar = 5
    };



    static char GetRandomCharacter(enCharType CharType)
    {
        if (CharType == MixChar)
        {
            CharType = (enCharType)RandomNumber(1, 3);
        }

        switch (CharType)
        {
        case enCharType::SmallLetter:
            return char(RandomNumber(97, 122));
            break;

        case enCharType::CapitalLetter:
            return char(RandomNumber(65, 90));
            break;

        case enCharType::SpecialCharacter:
            return char(RandomNumber(33, 47));
            break;

        case enCharType::Digit:
            return char(RandomNumber(48, 57));
            break;

        }

    }

    //*********************************************************
    //Generate Word

    static string GenerateWord(enCharType CharType, short CharNumber)
    {
        string Word;
        for (short i = 0; i <= CharNumber; i++)
        {
            Word += GetRandomCharacter(CharType);
        }
        return Word;
    }


    //*********************************************************
    //Generate Key

    static string GeneratKey(enCharType CharType)
    {
        string Key = "";
        short Length = 4;

        Key = GenerateWord(CharType, Length) + "-";
        Key = Key + GenerateWord(CharType, Length) + "-";
        Key = Key + GenerateWord(CharType, Length) + "-";
        Key = Key + GenerateWord(CharType, Length);

        return Key;
    }

    //*********************************************************
    //Generate Keys

    static string Separator(int Counter)
    {
        if (Counter >= 100)
        {
            return ": ";
        }
        else if (Counter < 10)
        {
            return "  : ";
        }

        else
            return " : ";
    }

    static void GeneratKeys(short NumberOfKeys, enCharType CharType)
    {
        for (int i = 1; i <= NumberOfKeys; i++)
        {

            cout << "[" << i << "]" << Separator(i);

            cout << GeneratKey(CharType) << endl;
        }
    }

    //*********************************************************
    // Swap Functions//
    //Swap int
    static void Swap(int& A, int& B)
    {
        int Temp;
        Temp = A;
        A = B;
        B = Temp;
    }

    //Swap double
    static void Swap(double& A, double& B)
    {
        double Temp;
        Temp = A;
        A = B;
        B = Temp;
    }

    //Swap string
    static void Swap(string& A, string& B)
    {
        string Temp;
        Temp = A;
        A = B;
        B = Temp;
    }

    //*********************************************************
    // Shuffle Array Number

    static void ShuffleArray(int arr[10], int arrLength)
    {
        for (int i = 0; i < arrLength; i++)
        {
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
        }
    }

    // Shuffle Array of string

    static void ShuffleArray(string arr[5], int arrLength)
    {
        for (int i = 0; i < arrLength; i++)
        {

        }
    }

    //*********************************************************
    // Fill Array With Random Number
    static void FillArrayWithRandomNumbers(int arr[100], int arrLength, int From, int To)
    {
        for (int i = 0; i < arrLength; i++)
        {
            arr[i] = RandomNumber(From, To);
        }
    }

    // Fill Array With Random Words
    static void FillArrayWithRandomWords(string arr[100], int arrLength, enCharType CharType, short CharNumber)
    {
        for (int i = 0; i < arrLength; i++)
        {
            arr[i] = GenerateWord(CharType, CharNumber);
        }
    }

    // Fill Array With Random Keys
    static void FillArrayWithRandomKeys(string arr[100], int arrLength, enCharType CharType)
    {
        for (int i = 0; i < arrLength; i++)
        {
            arr[i] = GeneratKey(CharType);
        }
    }

    //*********************************************************
    // Tabs Function
    static string Tabs(short NumberOfTabs)
    {
        string t = "";
        for (int i = 1; i < NumberOfTabs; i++)
        {
            t = t + "\t";
            cout << t;
        }
        return t;
    }

    //*********************************************************
    // Encryption  Function
    static string Encryption(string Text, short EncryptionKey)
    {
        for (int i = 0; i <= Text.length(); i++)
        {
            Text[i] = char((int)Text[i] + EncryptionKey);
        }

        return Text;
    }

    // Decryption Function
    static string Decryption(string Text, short EncryptionKey)
    {
        for (int i = 0; i <= Text.length(); i++)
        {
            Text[i] = char((int)Text[i] - EncryptionKey);
        }

        return Text;
    }


    //*********************************************************
    // Number To Text  Function
    static string NumberToText(int Number)
    {
        if (Number == 0)
        {
            return "";
        }

        if (Number >= 1 && Number <= 19)
        {
            string Arr[] = { "", "one", "Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten",
                "Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen"
            };

            return Arr[Number] + " ";
        }

        if (Number >= 20 && Number <= 99)
        {
            string Arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };

            return Arr[Number / 10] + " " + NumberToText(Number % 10);
        }

        if (Number >= 100 && Number <= 199)
        {
            return "One Hundred " + NumberToText(Number % 100);
        }

        if (Number >= 200 && Number <= 999)
        {
            return NumberToText(Number / 100) + "Hundred " + NumberToText(Number % 100);
        }

        if (Number >= 1000 && Number <= 1999)
        {
            return "One Thousend " + NumberToText(Number % 1000);
        }

        if (Number >= 2000 && Number <= 999999)
        {
            return NumberToText(Number / 1000) + "Thousend " + NumberToText(Number % 1000);
        }

        if (Number >= 1000000 && Number <= 1999999)
        {
            return "One Million " + NumberToText(Number % 1000000);
        }

        if (Number >= 2000000 && Number <= 999999999)
        {
            return NumberToText(Number / 1000000) + "Million " + NumberToText(Number % 1000000);
        }

        if (Number >= 1000000000 && Number <= 1999999999)
        {
            return "One Billion " + NumberToText(Number % 1000000000);
        }

        else
        {
            return NumberToText(Number / 1000000000) + "Billion " + NumberToText(Number % 1000000000);
        }



    }

    //*********************************************************
    // Encryption  Function

    static string  EncryptText(string Text, short EncryptionKey = 2)
    {

        for (int i = 0; i <= Text.length(); i++)
        {

            Text[i] = char((int)Text[i] + EncryptionKey);

        }

        return Text;

    }

    //*********************************************************
    // Decryption  Function

    static string  DecryptText(string Text, short EncryptionKey = 2)
    {

        for (int i = 0; i <= Text.length(); i++)
        {

            Text[i] = char((int)Text[i] - EncryptionKey);

        }
        return Text;

    }


};

