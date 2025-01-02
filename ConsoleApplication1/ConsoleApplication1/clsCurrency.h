#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include <vector>
#include <fstream>
using namespace std;

class clsCurrency
{
private:
	enum enMode{ EmptyMode = 0 , UpdateMode = 1};
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	//****************************************************************************************************
    //Convert Currency Object To Line

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Separator = "#//#")
	{

		string CurrencyRecord = "";
		CurrencyRecord += Currency.Country() + Separator;
		CurrencyRecord += Currency.CurrencyCode() + Separator;
		CurrencyRecord += Currency.CurrencyName() + Separator;
		CurrencyRecord += to_string(Currency.Rate());
		
		return CurrencyRecord;

	}

	//****************************************************************************************************
	//Convert Line To Currency Object

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Separator = "#//#")
	{
		vector<string> vCurrency;
		vCurrency = clsString::Split(Line, Separator);

		return clsCurrency(enMode::UpdateMode, vCurrency[0], vCurrency[1], vCurrency[2],
			stoi(vCurrency[3]));

	}

	//****************************************************************************************************
	//Load Currency Data From File

	static  vector <clsCurrency> _LoadCurrencyDataFromFile()
	{

		vector <clsCurrency> vCurrency;

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				vCurrency.push_back(Currency);
			}

			MyFile.close();

		}

		return vCurrency;

	}

	//****************************************************************************************************
	//Save Currency Data To File

	static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrency)
	{

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (clsCurrency C : vCurrency)
			{
					//we only write records that are not marked for delete.  
					DataLine = _ConvertCurrencyObjectToLine(C);
					MyFile << DataLine << endl;

			}

			MyFile.close();

		}

	}

	//****************************************************************************************************
	void _Update()
	{
		vector <clsCurrency> _vCurrency;
		_vCurrency = _LoadCurrencyDataFromFile();

		for (clsCurrency& C : _vCurrency)
		{
			if (C.CurrencyCode() == CurrencyCode())
			{
				C = *this;
				break;
			}
		}


		_SaveCurrencyDataToFile(_vCurrency);
	}

	//****************************************************************************************************

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

	//####################################################################################################

public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode,
		string CurrencyName, float Rate)
	{
		_Mode         = Mode;
		_Country      = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate         = Rate;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string Country()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	//****************************************************************************************************

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	float Rate()
	{
		return _Rate;
	}

	//****************************************************************************************************

	static vector <clsCurrency> GetAllUSDRates()
	{

		return _LoadCurrencyDataFromFile();

	}

	//****************************************************************************************************
	// Finde Currency By Code

	static   clsCurrency FindByCode(string CurrencyCode)
	{

		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (Currency.CurrencyCode() == CurrencyCode)
				{
					MyFile.close();
					return Currency;
				}
			}

			MyFile.close();

		}

		return _GetEmptyCurrencyObject();

	}

	//****************************************************************************************************
	// Finde Currency By Country

	static   clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::UpperAllString(Currency.Country()) == Country)
				{
					MyFile.close();
					return Currency;
				}

			}

			MyFile.close();

		}

		return _GetEmptyCurrencyObject();

	}

	//****************************************************************************************************
	// Is Currency Exist

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);
		return (!C1.IsEmpty());

	}

	//****************************************************************************************************
	// Get Currencies List

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencyDataFromFile();
	}

	//****************************************************************************************************
	// Convert To USD

	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / Rate());
	}

	//****************************************************************************************************
	// Convert To Other Currency

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return (float)(AmountInUSD * Currency2.Rate());

	}

};

