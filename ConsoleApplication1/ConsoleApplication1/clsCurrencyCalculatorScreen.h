#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include <string>

using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:
    static void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:")
    {
        cout << "\n"<< Title << "";
        cout << "\n___________________";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();
        cout << "\n___________________\n";

    }


    static clsCurrency _GetCurrency(string Message)
    {

        string CurrencyCode;
        cout << Message << endl;

        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        return Currency;

    }

    static float _ExchangeAmount(string Massage)
    {
        cout << Massage;
        float Amount = clsInputValidate::ReadFloatNumber();
        return Amount;
    }


    static void _PrintCalculationsResults(clsCurrency Currency1, clsCurrency Currency2 , float AmountToExchange)
    {
        _PrintCurrencyCard(Currency1, "Convert From:");
        float AmountInUSD = Currency1.ConvertToUSD(AmountToExchange);

        cout << AmountToExchange << " " << Currency1.CurrencyCode()
            << " = " << AmountInUSD << " USD\n";

        if (Currency2.CurrencyCode() == "USD")
        {
            return;
        }

        cout << "\nConverting from USD to:\n";

        _PrintCurrencyCard(Currency2, "To:");

        float AmountInCurrency2 = Currency1.ConvertToOtherCurrency(AmountToExchange, Currency2);

        cout << AmountToExchange << " " << Currency1.CurrencyCode()
            << " = " << AmountInCurrency2 << " " << Currency2.CurrencyCode();
    }

public:

    static void ShowCurrencyCalculatorScreen()
    {
        char Continue = 'y';

        while (Continue == 'y' || Continue == 'Y')
        {
            system("cls");
            _DrawScreenHeader("\t  Currency Calculator Screen");

            clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency Code From : ");
            clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency Code To  : ");
            float AmountToExchange = _ExchangeAmount("\nPlease Enter Amount to Exchange : ");

            _PrintCalculationsResults(CurrencyFrom, CurrencyTo, AmountToExchange);

            cout << "\n\nDo you want to perform another calculation? y/n ? ";
            cin >> Continue;

        }

    }
};

