#pragma once

#include <Windows.h>
#include <windowsx.h>
#include <ctime>
#include "resource.h"

//Dùng để sử dụng hàm StrCpy, StrNCat
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

#include "UpdateFormAddCallBack.h"
#include "FormAddExpenseLogic.h"

#define MAX_LEN 256

class FormAddExpense : public UpdateFormAddCallback
{
private:
	HINSTANCE mHInst;
	HWND mHParent;
	HWND mHCombobox;
	HWND mHContent;
	HWND mHMoney;
	HWND mHMonth;
	HWND mHYear;

	int mID;

	FormAddExpenseLogic* myHandler;

public:
	FormAddExpense();

	~FormAddExpense();

	void createForm(HWND hParent, long ID, HINSTANCE hInst);

	void addExpense(TCHAR* type, TCHAR* name, TCHAR* money);

	void initAllTypeCallBack(vector<TCHAR*> listType);

	void initAllType();

	TCHAR* getCurType();

	TCHAR* getCurContent();

	TCHAR* getCurMoney();

	int getMonth();

	int getYear();

};

