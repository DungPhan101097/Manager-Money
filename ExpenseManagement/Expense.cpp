#include "stdafx.h"
#include "Expense.h"
//#include <iodateeam>
#include <iostream>

Expense::Expense(TCHAR* type, TCHAR* name, int money, unsigned char day, unsigned char month, int year)
{
	mType = type;
	mName = name;
	mMoney = money;
	mDay = day;
	mMonth = month;
	mYear = year;
}

Expense::~Expense()
{
}

TCHAR* Expense::getType()
{
	return mType;
}

int Expense::getMoney()
{
	return mMoney;
}

TCHAR* Expense::getContent()
{
	return mName;
}


void Expense::printExpense()
{
	cout << "Noi dung: " << mName << " So tien : " << mMoney;
}


TCHAR* Expense::getExpense()
{
	TCHAR* date = new TCHAR[256];
	
	
	StrCpy(date, mType);
	StrCat(date, _T("\n"));
	StrCat(date, mName);
	StrCat(date, _T("\n"));
	TCHAR* buffer = new TCHAR[RADIX];
	_itow(mMoney, buffer, RADIX);
	StrCat(date, buffer );
	StrCat(date, _T("\n"));
	_itow(mDay, buffer, RADIX);
	StrCat(date, buffer);
	StrCat(date, _T("/"));
	_itow(mMonth, buffer, RADIX);
	StrCat(date, buffer);
	StrCat(date, _T("/"));
	_itow(mYear, buffer, RADIX);
	StrCat(date, buffer);

	return date;
}

unsigned char Expense::getMonth()
{
	return mMonth;
}

int Expense::getYear()
{
	return mYear;
}

unsigned char Expense::getDay()
{
	return mDay;
}

TCHAR* Expense::getDate()
{
	TCHAR* date = new TCHAR[20];
	TCHAR* buffer = new TCHAR[5];
	_itow(mDay, buffer, RADIX);
	StrCpy(date, buffer);
	StrCat(date, _T("/"));
	_itow(mMonth, buffer, RADIX);
	StrCat(date, buffer);
	StrCat(date, _T("/"));
	_itow(mYear, buffer, RADIX);
	StrCat(date, buffer);

	return date;
}
