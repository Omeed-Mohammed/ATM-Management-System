#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsString.h"
#include "clsPerson.h"




using namespace std;

class clsBankClient : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1 , AddNewMode = 2};
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;

    //*****************************************************************
    // Function Convert Line to Client Object

    string _PrepareTransferLogRecord(float TransferAmount, clsBankClient DestinationClient , string UserName, string Separator = "#//#")
    {
        
        string TransferRecord = "";
        TransferRecord += clsDate::GetSystemDateTimeString() + Separator;
        TransferRecord += AccountNumber() + Separator;
        TransferRecord += DestinationClient.AccountNumber() + Separator;
        TransferRecord += to_string(TransferAmount) + Separator;
        TransferRecord += to_string(AccountBalance) + Separator;
        TransferRecord += to_string(DestinationClient.AccountBalance) + Separator;
        TransferRecord += CurrentUser.UserName ;
        return TransferRecord;
    }


    //****************************************************************************************************
    // Register Transfer Log
    void _RegisterTransferLog(float TransferAmount,
        clsBankClient DestinationClient,string UserName )
    {

        string stDataLine = _PrepareTransferLogRecord(TransferAmount, DestinationClient, UserName);

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    //****************************************************************************************************
    // Register Transfer Log

    struct sTransferLogRecord;
    static sTransferLogRecord _ConvertTransferLogDateInfo(string Line, string Separator = "#//#")
    {
        sTransferLogRecord TransferLogRecord;
        vector<string> vTransferLogDateLine;
        vTransferLogDateLine = clsString::Split(Line, Separator);

        TransferLogRecord.Date                     = vTransferLogDateLine[0];
        TransferLogRecord.AccountNumberSource      = vTransferLogDateLine[1];
        TransferLogRecord.AccountNumberDestination = vTransferLogDateLine[2];
        TransferLogRecord.Amount = stoi(vTransferLogDateLine[3]);
        TransferLogRecord.AccountBalanceSource = stoi(vTransferLogDateLine[4]);
        TransferLogRecord.AccountBalanceDestination = stoi(vTransferLogDateLine[5]);
        TransferLogRecord.User = vTransferLogDateLine[6];
        
        return TransferLogRecord;
    }


    //*****************************************************************
    // Function Convert Line to Client Object

    static clsBankClient _ConvertLineToClientObject(string Line, string separator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, separator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

    }

    //*****************************************************************
    // Function Convert Client Object to Line
    
    static string _ConvertClientObjectToLine(clsBankClient Client, string separator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + separator;
        stClientRecord += Client.LastName + separator;
        stClientRecord += Client.Email + separator;
        stClientRecord += Client.Phone + separator;
        stClientRecord += Client.AccountNumber() + separator;
        stClientRecord += Client.PinCode + separator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;

    }


    //*****************************************************************
    // Function Get Empty Client Object

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    //*****************************************************************
    // Function Load Clients Date From File

    static vector<clsBankClient>_LoadClientsDataFromFile()
    {
        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode
        if (MyFile.is_open())
        {
            string Line;
            
            while (getline(MyFile, Line))
            {
               clsBankClient Client = _ConvertLineToClientObject(Line);
                vClients.push_back(Client);
            }
            MyFile.close();

        }
        return vClients;
    }

    //*****************************************************************
    // Function Load Clients Date From File

    static void _SaveClientsDateToFile(vector<clsBankClient>_vClients)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);
        string DateLine;
        if (MyFile.is_open())
        {
            for (clsBankClient C : _vClients)
            {
                if (C.MarkedForDelete() == false)
                {
                    //We only write records that are not marked for delete.
                    DateLine = _ConvertClientObjectToLine(C);
                    MyFile << DateLine << endl;
                }
            }
            MyFile.close();
        }
    }

    //*****************************************************************
    // Function Update

    void _Update()
    {
        vector<clsBankClient>_vClient;
        _vClient = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClient)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }
        }

        _SaveClientsDateToFile(_vClient);
    }

    //*****************************************************************
   // Function Add Data Line To File

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }


    //*****************************************************************
    // Function Add New

    void _AddNew()
    {

        _AddDataLineToFile(_ConvertClientObjectToLine(*this));
    }


public:
    //*****************************************************************
    // Constructor

    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }

    struct sTransferLogRecord
    {
        string Date;
        string AccountNumberSource;
        string AccountNumberDestination;
        float Amount;
        float AccountBalanceSource;
        float AccountBalanceDestination;
        string User;
        
    
    };


    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDelete()
    {
        return _MarkedForDelete;
    }

    //*****************************************************************
    
    //Get Function
    string AccountNumber()
    {
        return _AccountNumber;
    }

    //*****************************************************************
    //Set Function
    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    //Get Function
    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    //*****************************************************************

    //Set Function
    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    //Get Function
    float GetAccountBalance()
    {
        return _AccountBalance;
    }

    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) 
        float AccountBalance;

    //*****************************************************************
    /*
    void Print()
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << FirstName;
        cout << "\nLastName    : " << LastName;
        cout << "\nFull Name   : " << FullName();
        cout << "\nEmail       : " << Email;
        cout << "\nPhone       : " << Phone;
        cout << "\nAcc. Number : " << _AccountNumber;
        cout << "\nPassword    : " << _PinCode;
        cout << "\nBalance     : " << _AccountBalance;
        cout << "\n___________________\n";

    }
    */
    //*****************************************************************
    //Function Find Client

    static clsBankClient Find(string AccountNumber)
    {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }


    //*****************************************************************
    //Function Find Client with Account Number & Pin code

    static clsBankClient Find(string AccountNumber, string PinCode)
    {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }
        return _GetEmptyClientObject();
    }

    //*****************************************************************
    //Function Client Exist

    static bool IsClientExist(string AccountNumber)
    {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        return (!Client1.IsEmpty());
    }

    //*****************************************************************
    //Function Get Add New Client Object


    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }


    //*****************************************************************
    //Function Save

    enum enSaveResult{svFaildEmptyObject = 0, svSucceeded = 1 , svFaildAccountNumberExist = 2};
    enSaveResult Save()
    {
        switch (_Mode)
        {
            case enMode::EmptyMode:
            {
                return enSaveResult::svFaildEmptyObject;
            }

            case enMode::UpdateMode:
            {
                _Update();
                return enSaveResult::svSucceeded;

                break;
            }
            case enMode::AddNewMode:
            {
                if (clsBankClient::IsClientExist(_AccountNumber))
                {
                    return enSaveResult::svFaildAccountNumberExist;
                }
                else
                {
                    _AddNew();
                    _Mode = enMode::UpdateMode;
                    return enSaveResult::svSucceeded;
                }
            }

        }
            
    }

    //*****************************************************************
    //Function Delete

    bool Delete()
    {
        vector<clsBankClient>_vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == _AccountNumber)
            {
                C._MarkedForDelete = true;
                break;
            }
        }

        _SaveClientsDateToFile(_vClients);

        *this = _GetEmptyClientObject();

        return true;
    }


    //*****************************************************************
    //Function Get Clients List

    static vector<clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    //*****************************************************************
    //Function Get Total Balances

    static double GetTotalBalances()
    {
        vector<clsBankClient>vClients = GetClientsList();
        double TotalBalances = 0;

        for (clsBankClient Client : vClients)
        {
            
            TotalBalances += Client.AccountBalance;

            
        }
        return TotalBalances;
    }

    //*****************************************************************
    //Function Deposit

    void Deposit(double Amount)
    {
        _AccountBalance += Amount;
        Save();

    }


    //*****************************************************************
    //Function Withdraw

    bool Withdraw(double Amount)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }
        else
        {
            _AccountBalance -= Amount;
            Save();
        }
        
    }

    //*****************************************************************
    //Function Transfer

    bool Transfer(float Amount, clsBankClient& DestinationClient , string UserName)
    {
        if (Amount > AccountBalance)
        {
            return false;
        }

        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterTransferLog(Amount, DestinationClient, UserName);
        return true;

    }

    //****************************************************************************************************
    // Load Register Data From File
    static  vector <sTransferLogRecord> GetTransferLogList()
    {

        vector <sTransferLogRecord> vTransferLogRecord;

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                sTransferLogRecord TransferLogInfo = _ConvertTransferLogDateInfo(Line);

                vTransferLogRecord.push_back(TransferLogInfo);
            }

            MyFile.close();

        }

        return vTransferLogRecord;

    }

    




};

