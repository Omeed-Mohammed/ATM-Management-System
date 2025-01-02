#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsString.h"
#include "clsPerson.h"
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;

class clsUser : public clsPerson
{
private:
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;
    
    bool _MarkedForDelete = false;

    


    //****************************************************************************************************
    //Prepare LogIn Record
    string _PrepareLogInRecord(string Separator = "#//#")
    {
        string LoginRecord = "";
        LoginRecord += clsDate::GetSystemDateTimeString() + Separator;
        LoginRecord += UserName + Separator;
        LoginRecord += clsUtil::EncryptText(Password) + Separator;
        LoginRecord += to_string(Permissions);
        return LoginRecord;
    }

    
    //****************************************************************************************************
  // Load Register Data From File
    struct sLoginRegisterRecord;
    static sLoginRegisterRecord _ConvertRegisterDataToLoginInfo(string Line, string Separator = "#//#")
    {
        sLoginRegisterRecord LoginRegisterRecord;
        vector<string> vLoginRegisterDateLine;
        vLoginRegisterDateLine = clsString::Split(Line, Separator);

        LoginRegisterRecord.Date        = vLoginRegisterDateLine[0];
        LoginRegisterRecord.UserName    = vLoginRegisterDateLine[1];
        LoginRegisterRecord.Password = clsUtil::DecryptText(vLoginRegisterDateLine[2]);
        LoginRegisterRecord.Permissions = stoi(vLoginRegisterDateLine[3]);

        return LoginRegisterRecord;
    }


    //****************************************************************************************************
    //Convert Line To User Object

    static clsUser _ConvertLineToUserObject(string Line, string Separator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Separator);

        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));

    }

    //****************************************************************************************************
    //Get Empty User Object


    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    //****************************************************************************************************
    //Convert User Object To Line

    static string _ConvertUserObjectToLine(clsUser User, string Separator = "#//#")
    {
        
        string UserRecord = "";
        UserRecord += User.FirstName + Separator;
        UserRecord += User.LastName + Separator;
        UserRecord += User.Email + Separator;
        UserRecord += User.Phone + Separator;
        UserRecord += User.UserName + Separator;
        UserRecord += clsUtil::EncryptText(User.Password) + Separator;
        UserRecord += to_string(User.Permissions);

        return UserRecord;

    }


    //****************************************************************************************************
    //Load Users Data From File

    static  vector <clsUser> _LoadUsersDataFromFile()
    {

        vector <clsUser> vUsers;

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsUser User = _ConvertLineToUserObject(Line);

                vUsers.push_back(User);
            }

            MyFile.close();

        }

        return vUsers;

    }

    //****************************************************************************************************
    //Save Users Data To File

    static void _SaveUsersDataToFile(vector <clsUser> vUsers)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsUser U : vUsers)
            {
                if (U.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConvertUserObjectToLine(U);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }

    //****************************************************************************************************
    //Update

    void _Update()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == UserName)
            {
                U = *this;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

    }

    //****************************************************************************************************
    //AddNew

    void _AddNew()
    {

        _AddDataLineToFile(_ConvertUserObjectToLine(*this));
    }

    //****************************************************************************************************
    //AddNew

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }


    //####################################################################################################
    //####################################################################################################
public:
    enum enPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTranactions = 32, 
        pManageUsers = 64 , pLoginRegister = 128 , pCurrancyExchange = 256
    };

    clsUser(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string UserName, string Password,
        int Permissions) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    struct sLoginRegisterRecord
    {
        string Date;
        string UserName;
        string Password;
        int Permissions;
    };

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }


    //****************************************************************************************************
    //Get & Set UserName
    string GetUserName()
    {
        return _UserName;
    }

    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }

    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

    //****************************************************************************************************
    //Get & Set Password

    void SetPassword(string Password)
    {
        _Password = Password;
    }

    string GetPassword()
    {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    //****************************************************************************************************
    //Get & Set Permissions

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    int GetPermissions()
    {
        return _Permissions;
    }
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

    //****************************************************************************************************
    // Find By UserName 


    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLineToUserObject(Line);
                if (User.UserName == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();

        }

        return _GetEmptyUserObject();
    }


    //Find By UserName & Password

    static clsUser Find(string UserName, string Password)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLineToUserObject(Line);
                if (User.UserName == UserName && User.Password == Password)
                {
                    MyFile.close();
                    return User;
                }

            }

            MyFile.close();

        }
        return _GetEmptyUserObject();
    }

    //****************************************************************************************************
    // Save

    enum enSaveResults { svFaildEmptyObject = 0, 
        svSucceeded = 1, svFaildUserExists = 2 };

    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        }

        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsUser::IsUserExist(_UserName))
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                _AddNew();
                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }

    }

    //****************************************************************************************************
    // Is User Exist
    static bool IsUserExist(string UserName)
    {

        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }

    //****************************************************************************************************
    // Delete

    bool Delete()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == _UserName)
            {
                U._MarkedForDelete = true;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

        *this = _GetEmptyUserObject();

        return true;

    }

    //****************************************************************************************************
    // Get Add New User Object

    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    //****************************************************************************************************
    // Get Users List

    static vector <clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();

    }

    //****************************************************************************************************
    // Check Access Permission

    bool CheckAccessPermission(enPermissions Permission)
    {
        if (this->Permissions == enPermissions::eAll)
        {
            return true;
        }
        if ((Permission & this->Permissions) == Permission)
        {
            return true;
        }
        else
            return false;
    }


    //****************************************************************************************************
    // Register LogIn
    void RegisterLogIn()
    {

        string stDataLine = _PrepareLogInRecord();

        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

  

    //****************************************************************************************************
    // Load Register Data From File
    static  vector <sLoginRegisterRecord> GetLoginRegisterList()
    {

        vector <sLoginRegisterRecord> vLoginRegisterRecord;

        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                sLoginRegisterRecord LoginInfo = _ConvertRegisterDataToLoginInfo(Line);

                vLoginRegisterRecord.push_back(LoginInfo);
            }

            MyFile.close();

        }

        return vLoginRegisterRecord;

    }

};

