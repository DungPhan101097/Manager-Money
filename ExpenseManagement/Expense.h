#pragma once
#include <string>
//Dùng để sử dụng hàm StrCpy, StrNCat
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#include "DefineHeader.h"

using namespace std;

class Expense
{
private:
	TCHAR* mType;
	TCHAR* mName;
	int mMoney;
	unsigned char mDay;
	unsigned char mMonth;
	int mYear;

public:
	Expense(TCHAR* type, TCHAR* name, int money, unsigned char day, unsigned char month, int year);

	~Expense();

	TCHAR* getType();

	TCHAR* getContent();

	int getMoney();

	void printExpense();

	unsigned char getMonth();

	int getYear();

	unsigned char getDay();

	TCHAR* getExpense();

	TCHAR* getDate();
	
};

