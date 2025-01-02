#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "Global.h"
#include "clsUser.h"
#include "clsDate.h"


using namespace std;
class clsScreen 
{
protected:

    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << setw(37) << left << "" << "___________________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t     ___________________________________________\n\n";

        
        cout << setw(37) << left << "" << "User: ";
        cout << CurrentUser.UserName << endl;
        cout << setw(37) << left << "" << "Date: " <<clsDate::DateToString(clsDate());
        cout << endl ;
        
        
    }


    //***********************************************************************************
    static bool CheckAccessRights(clsUser::enPermissions Permission)
    {

        if (!CurrentUser.CheckAccessPermission(Permission))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else
        {
            return true;
        }
    }

    //***********************************************************************************
    


};

