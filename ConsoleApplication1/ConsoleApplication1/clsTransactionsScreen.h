#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include <iomanip>
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferLogListScreen.h"
#include "clsTransferScreen.h"
using namespace std;

class clsTransactionsScreen : protected clsScreen
{
private:
    enum enTransactionsMenuOptions
    {
        eDeposit = 1, eWithdraw = 2, eShowTotalBalances = 3,
       eShowTransferScreen = 4 , eTransferLog = 5 , eShowMainMenu = 6
    };

    static int ReadTransactionsMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        int Choice = clsInputValidate::ReadShortNumberBetween(1, 6);
        return Choice;
    }
    //*************************************************************************
    // Show Deposit Screen
    static void _ShowDepositScreen()
    {
        //cout << "\n Deposit Screen will be here.\n";
        clsDepositScreen::ShowDepositScreen();

    }

    //*************************************************************************
    // Show Withdraw Screen


    static void _ShowWithdrawScreen()
    {
        //cout << "\n Withdraw Screen will be here.\n";
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    //*************************************************************************
    // Show Total Balances Screen

    static void _ShowTotalBalancesScreen()
    {
       // cout << "\n Balances Screen will be here.\n";
        clsTotalBalancesScreen::ShowTotalBalances();
    }

    //*************************************************************************
    // Show Transfer Screen

    static void _ShowTransferScreen()
    {
        //cout << "\n Balances Screen will be here.\n";
        clsTransferScreen::ShowTransferScreen();

    }

    //*************************************************************************
   // Show Transfer Log Screen

    static void _ShowTransferLogScreen()
    {
        //cout << "\n Balances Screen will be here.\n";
        clsTransferLogListScreen :: ShowTransferLogScreen();
    }

    //*************************************************************************
    // GoBack To Transactions Menu

    static void _GoBackToTransactionsMenu()
    {
        cout << "\n\nPress any key to go back to Transactions Menu...";
        system("pause>0");
        ShowTransactionsMenu();

    }

   
    //*************************************************************************
    // Perform Transactions Menu Option

    static void _PerformTransactionsMenuOption(enTransactionsMenuOptions TransactionsMenuOption)
    {
        switch (TransactionsMenuOption)
        {
            case enTransactionsMenuOptions::eDeposit:
            {
                system("cls");
                _ShowDepositScreen();
                _GoBackToTransactionsMenu();
                break;
            }

            case enTransactionsMenuOptions::eWithdraw:
            {
                system("cls");
                _ShowWithdrawScreen();
                _GoBackToTransactionsMenu();
                break;
            }

            case enTransactionsMenuOptions::eShowTotalBalances:
            {
                system("cls");
                _ShowTotalBalancesScreen();
                _GoBackToTransactionsMenu();
                break;
            }

            case enTransactionsMenuOptions::eShowTransferScreen:
            {
                system("cls");
                _ShowTransferScreen();
                _GoBackToTransactionsMenu();
                break;
            }

            case enTransactionsMenuOptions::eTransferLog:
            {
                system("cls");
                _ShowTransferLogScreen();
                _GoBackToTransactionsMenu();
                break;
            }

            case enTransactionsMenuOptions::eShowMainMenu:
            {
               // clsMainScreen::ShowMainManu();
            }
        }


    }



public:
    static void ShowTransactionsMenu()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pTranactions))
        {
            return;// this will exit the function and it will not continue
        }

        system("cls");
        _DrawScreenHeader("\t  Transactions Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransactionsMenuOption((enTransactionsMenuOptions)ReadTransactionsMenuOption());
    }
};

