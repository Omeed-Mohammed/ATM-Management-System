#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"


using namespace std;

class clsLoginScreen :protected clsScreen
{

private:

    static  bool _Login()
    {
        bool LoginFailed = false;
        short FailedLogenCount = 0;

        string Username, Password;
        do
        {

            if (LoginFailed)
            {
                FailedLogenCount++;
                
                cout << "\nInvalid Username/Password!\n\n";
                cout << "\nYou have "<<(3- FailedLogenCount)
                    <<" Trials to Login\n\n";
               
            }

            if (FailedLogenCount == 3)
            {
                cout << "\nYou are Locked after 3 Failed Trails\n\n";
                return false;
            }

            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFailed = CurrentUser.IsEmpty();

        } while (LoginFailed);

        CurrentUser.RegisterLogIn();
        clsMainScreen::ShowMainManu();
        

    }

public:


    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
       return _Login();
       

    }

};

