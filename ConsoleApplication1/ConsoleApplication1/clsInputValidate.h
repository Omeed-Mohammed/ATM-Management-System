#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include "clsDate.h"
#include <cstdlib>

using namespace std;
class clsInputValidate
{
public:

	static bool IsNumberBetween(int Number, int From, int To)
	{
		return (Number >= From && Number <= To) ? true : false;
	}

	static bool IsNumberBetween(double Number, double From, double To)
	{
		return (Number > From && Number < To) ? true : false;
	}

	static bool IsNumberBetween(short Number, short From, short To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}


	//********************************************************************************************
	//Function Is Date Between

	static bool IsDateBetween(clsDate Date, clsDate DateFrom, clsDate DateTo)
	{
		//Date>=From && Date<=TO
		if ((clsDate::IsDate1AfterDate2(Date, DateFrom) || clsDate::IsDate1EqualDate2(Date, DateFrom))
			&& (clsDate::IsDate1BeforeDate2(Date, DateTo) || clsDate::IsDate1BeforeDate2(Date, DateTo)))
		{
			return true;
		}

		if ((clsDate::IsDate1AfterDate2(Date, DateTo) || clsDate::IsDate1EqualDate2(Date, DateTo))
			&& (clsDate::IsDate1BeforeDate2(Date, DateFrom) || clsDate::IsDate1BeforeDate2(Date, DateFrom)))
		{
			return true;
		}

		return false;
	}


	//********************************************************************************************
	//Function Read Number

	static int ReadIntNumber()
	{
		int Number = 0;
		string massage = "Invalid Number, Enter again\n";
		cin >> Number;
		while (Number < 0)
		{
			cout << massage;
			cin >> Number;
		} 

		return Number;

	}


	static short ReadShortNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		short Number;
		cin >> Number;
		while (cin.fail())
		{
			// user didn't input a number    
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage << endl;
			cin >> Number;

		}

		return Number;


	}

	//********************************************************************************************
	//Function Read iNT Number Between

	static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		int Number = ReadIntNumber();
		//string ErrorMessage = "Number is not within range, Enter again:\n";

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadIntNumber();
		}
		return Number;
	}


	//********************************************************************************************
	//Function Read Short Number Between
	static short ReadShortNumberBetween(short From, short To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		short Number = ReadShortNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadShortNumber();
		}
		return Number;
	}

	//********************************************************************************************
	//Function Read Double Number


	static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		double Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	//********************************************************************************************
	//Function Read Double Number Between

	static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		double Number = ReadDblNumber();

		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadDblNumber();
		}
		return Number;
	}

	
	//********************************************************************************************
	//Function Read Float Number

	static double ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		float Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static double ReadFloatNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		float Number = ReadFloatNumber();

		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadDblNumber();
		}
		return Number;
	}
	//********************************************************************************************
	//Function Is Valide Date

	static bool IsValideDate(clsDate Date)
	{
		return	clsDate::IsValidDate(Date);
	}

	//********************************************************************************************
	//Function Read string

	static string ReadString()
	{
		string  S1 = "";
		// Usage of std::ws will extract allthe whitespace character
		getline(cin >> ws, S1);
		return S1;
	}






};

