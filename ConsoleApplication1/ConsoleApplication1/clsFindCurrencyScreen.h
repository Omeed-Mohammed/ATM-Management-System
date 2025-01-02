#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include <string>

using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
private:
    static void _PrintCurrencyInfo(clsCurrency Currency)
    {
        cout << "\nCurrency Card:";
        cout << "\n___________________";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();
        cout << "\n___________________\n";

    }

    static void _ShowResults(clsCurrency Currency)
    {
        if (!Currency.IsEmpty())
        {
            cout << "\nCurrency Found :-)\n";
            _PrintCurrencyInfo(Currency);
        }
        else
        {
            cout << "\nCurrency Was not Found :-(\n";
        }
    }

    
    
    //There are Two Functions Downe 

public:

    static void ShowFindCurrencyScreen()
    {

        _DrawScreenHeader("\t  Find Currency Screen");

        cout << "\nFind By: [1] Code or [2] Country ? ";
        short Answer = 1;

        cin >> Answer;

        if (Answer == 1)
        {
            string CurrencyCode;
            cout << "\nPlease Enter CurrencyCode: ";
            CurrencyCode = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
            _ShowResults(Currency);
        }
        else
        {
            string Country;
            cout << "\nPlease Enter Country Name: ";
            Country = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCountry(Country);
            _ShowResults(Currency);
        }






    }


};



/*
  static void _FindCurrencyByCode()
    {
        string CurrencyCode;
        cout << "\nPlease Enter Currency code: ";
        CurrencyCode = clsInputValidate::ReadString();
        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency code is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

        if (!Currency.IsEmpty())
        {
            cout << "\nCurrency Found :-)\n";
            _PrintCurrencyInfo(Currency);
        }
        else
        {
            cout << "\nCurrency Was not Found :-(\n";
        }

        
    }


    static void _FindCurrencyByCounty()
    {
        string CurrencyCountry;
        cout << "\nPlease Enter Currency Country: ";
        CurrencyCountry = clsInputValidate::ReadString();
        while (!clsCurrency::IsCurrencyExist(CurrencyCountry))
        {
            cout << "\nCurrency Country is not found, choose another one: ";
            CurrencyCountry = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCountry(CurrencyCountry);

        if (!Currency.IsEmpty())
        {
            cout << "\nCurrency Found :-)\n";
            _PrintCurrencyInfo(Currency);
        }
        else
        {
            cout << "\nCurrency Was not Found :-(\n";
        }

        
    }

*/

