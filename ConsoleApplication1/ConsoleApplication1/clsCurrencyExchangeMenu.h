#pragma once
#include <iostream>
#include "clsCurrency.h"
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;

class clsCurrencyExchangeMenu : protected clsScreen
{
private:
    enum enCurrencyMenuOptions
    {
        eListCurrencies = 1, eFindCurrency = 2, eUpdateCurrency = 3,
        eCurrencyCalculator = 4,  eShowMainMenu = 5
    };

    static int ReadTransactionsMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        int Choice = clsInputValidate::ReadShortNumberBetween(1, 5);
        return Choice;
    }

    //*************************************************************************
    // Show List Currencies

    static void _ShowListCurrencies()
    {
        //cout << "\n List Currencies will be here.\n";
        clsListCurrenciesScreen::ShowCurrencyListScreen();
    }

    //*************************************************************************
    // Show Find Currency

    static void _FindCurrency()
    {
        //cout << "\n Find Currency will be here.\n";
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    //*************************************************************************
    // Show Update Currency

    static void _ShowUpdateCurrency()
    {
        //cout << "\n Update Currency will be here.\n";
        clsUpdateCurrencyScreen::ShowUpdateCurrencyScreen();
    }

    //*************************************************************************
    // Show Currency Calculator

    static void _ShowCurrencyCalculator()
    {
        //cout << "\n Currency Calculator will be here.\n";
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }

    //*************************************************************************
    // GoBack To Currency Exchange Menu

    static void _GoBackToCurrencyExchangeMenu()
    {
        cout << "\n\nPress any key to go back to Currency Exchange Menu...";
        system("pause>0");
        ShowCurrencyExchangeMenu();

    }

    //*************************************************************************
    // Perform Currency Exchange Menu Option

    static void _PerformCurrencyExchangeMenuOption(enCurrencyMenuOptions CurrencyMenuOption)
    {
        switch (CurrencyMenuOption)
        {
            case enCurrencyMenuOptions::eListCurrencies:
            {
                system("cls");
                _ShowListCurrencies();
                _GoBackToCurrencyExchangeMenu();
                break;
            }

            case enCurrencyMenuOptions::eFindCurrency:
            {
                system("cls");
                _FindCurrency();
                _GoBackToCurrencyExchangeMenu();
                break;
            }

            case enCurrencyMenuOptions::eUpdateCurrency:
            {
                system("cls");
                _ShowUpdateCurrency();
                _GoBackToCurrencyExchangeMenu();
                break;
            }

            case enCurrencyMenuOptions::eCurrencyCalculator:
            {
                system("cls");
                _ShowCurrencyCalculator();
                _GoBackToCurrencyExchangeMenu();
                break;
            }



            case enCurrencyMenuOptions::eShowMainMenu:
            {
                // clsMainScreen::ShowMainManu();
            }

        }
        


    }



public:

        static void ShowCurrencyExchangeMenu()
        {
            if (!CheckAccessRights(clsUser::enPermissions::pCurrancyExchange))
            {
                return;// this will exit the function and it will not continue
            }
           

            system("cls");
            _DrawScreenHeader("\t  Currency Exchange Menu Screen");

            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t\t  Currency Exchange Menu\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
            cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
            cout << setw(37) << left << "" << "\t[3] Update Currency.\n";
            cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
            cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
            cout << setw(37) << left << "" << "===========================================\n";

            _PerformCurrencyExchangeMenuOption((enCurrencyMenuOptions)ReadTransactionsMenuOption());
        }
};

