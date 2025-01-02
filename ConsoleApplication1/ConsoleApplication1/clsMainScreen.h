#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsClientListSecreen.h"
#include "clsScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginScreen.h"
#include "Global.h"
#include "clsUser.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMenu.h"
#include <iomanip>
#include <string>
using namespace std;

class clsMainScreen : protected clsScreen
{
private:
    enum enMainMenuOptions{
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenu = 6,
        eManageUsers = 7, eLoginRegister = 8 , eCurrencyMenu = 9 ,eLogout = 10
    };

    //*************************************************************************
    //Read Main Menu Option

    static int _ReadMainMenuOption()
    {
        
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
        int Choice = clsInputValidate::ReadShortNumberBetween(1, 10);
        
        return Choice;
    }


    //*************************************************************************
    //GoBack To Main Menu
    static  void _GoBackToMainMenu()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menu...\n";

        system("pause>0");
        ShowMainManu();
    }

    //*************************************************************************
    //Show All Clients Screen
    static void _ShowAllClientsScreen()
    {
        
        clsClientListScreen::ShowClientsList();

    }

    //*************************************************************************
    //Show Add New Clients Screen

    static void _ShowAddNewClientsScreen()
    {
        //cout << "\nAdd New Client Screen Will be here...\n";
        clsAddNewClientScreen::ShowAddNewClientScreen();

    }

    //*************************************************************************
    //Show Delete Client Screen

    static void _ShowDeleteClientScreen()
    {
        //cout << "\nDelete Client Screen Will be here...\n";
        clsDeleteClientScreen::ShowDeleteClientScreen();

    }

    //*************************************************************************
    //Show Update Client Screen

    static void _ShowUpdateClientScreen()
    {
        //cout << "\nUpdate Client Screen Will be here...\n";
        clsUpdateClientScreen::ShowUpdateClientScreen();

    }

    //*************************************************************************
    //Show Find Client Screen

    static void _ShowFindClientScreen()
    {
        //cout << "\nFind Client Screen Will be here...\n";
        clsFindClientScreen::ShowFindClientScreen();


    }

    //*************************************************************************
    //Show Transactions Menu

    static void _ShowTransactionsMenu()
    {
        //cout << "\nTransactions Menu Will be here...\n";
        clsTransactionsScreen::ShowTransactionsMenu();

    }

    //*************************************************************************
    //Show Manage Users Menu

    static void _ShowManageUsersMenu()
    {
        //cout << "\nUsers Menu Will be here...\n";
        clsManageUsersScreen::ShowManageUsersMenu();

    }

    //*************************************************************************
    //Show Manage Users Menu

    static void _ShowLoginRegisterList()
    {
        //cout << "\nLogin Register List Will be here...\n";
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }

    //*************************************************************************
    //Show Currency Exchange Menu

    static void _ShowCurrencyExchangeMenu()
    {
        //cout << "\nCurrency Exchange Menu Will be here...\n";
        clsCurrencyExchangeMenu::ShowCurrencyExchangeMenu();
        
    }


    //*************************************************************************
    //Show End Screen
    
    /*
    static void _ShowEndScreen()
    {
        cout << "\nEnd Screen Will be here...\n";

    }
    */
    static void _Logout()
    {
        CurrentUser = clsUser::Find("", "");
        

    }

    //*************************************************************************
    //Perform Main Menu Option
    static void _PerformMainMenuOption(enMainMenuOptions MainMenuOption)
    {
        switch (MainMenuOption)
        {
        case enMainMenuOptions::eListClients:
        {
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenu();
            break;
        }
        case enMainMenuOptions::eAddNewClient:
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eShowTransactionsMenu:
            system("cls");
            _ShowTransactionsMenu();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eManageUsers:
            system("cls");
            _ShowManageUsersMenu();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eLoginRegister:
            system("cls");
            _ShowLoginRegisterList();
            _GoBackToMainMenu();

        case enMainMenuOptions::eCurrencyMenu:
            system("cls");
            _ShowCurrencyExchangeMenu();
            _GoBackToMainMenu();

        case enMainMenuOptions::eLogout:
            system("cls");
            _Logout();

            break;
        }
    }



public:
	static void ShowMainManu()
	{
        system("cls");
        _DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Register.\n";
        cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerformMainMenuOption((enMainMenuOptions)_ReadMainMenuOption());

	}
};

