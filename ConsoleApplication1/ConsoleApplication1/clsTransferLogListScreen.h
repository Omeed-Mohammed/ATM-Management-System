#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsBankClient.h"
#include "Global.h"
#include "clsDate.h"
#include "clsTransactionsScreen.h"

using namespace std;
class clsTransferLogListScreen : protected clsScreen
{
private:
    static void _PrintTransferLogRecordLine(clsBankClient::sTransferLogRecord Record)
    {


        cout << setw(8) << left << "" << "| " << setw(23) << left << Record.Date;
        cout << "| " << setw(8) << left << Record.AccountNumberSource;
        cout << "| " << setw(8) << left << Record.AccountNumberDestination;
        cout << "| " << setw(8) << left << Record.Amount;
        cout << "| " << setw(10) << left << Record.AccountBalanceSource;
        cout << "| " << setw(10) << left << Record.AccountBalanceDestination;
        cout << "| " << setw(8) << left << Record.User;


    }

public:

    static void ShowTransferLogScreen()
    {
        
        vector <clsBankClient::sTransferLogRecord> vTransferLogRecord = clsBankClient::GetTransferLogList();

        string Title = "\tLogin Register List Screen";
        string SubTitle = "\t    (" + to_string(vTransferLogRecord.size()) + ") User(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date Time";
        cout << "| " << left << setw(8) << "S.Acct";
        cout << "| " << left << setw(8) << "D.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "S.Balance";
        cout << "| " << left << setw(10) << "D.Balance";
        cout << "| " << left << setw(8) << "User";
        
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferLogRecord.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsBankClient::sTransferLogRecord Record : vTransferLogRecord)
            {

                _PrintTransferLogRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};

