#pragma once
#include "UpdateFormStatisticalCallBack.h"
#include "FormStatisticalLogic.h"
#include "DefineHeader.h"


//Dùng để sử dụng hàm StrCpy, StrNCat
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

#define RADIX 10
#define MAX_LEN_MONEY 10
#define MAX_LEN 128


class FormStatistical :public UpdateStatisticalCallBack
{
private:
	HINSTANCE mHinst;
	HWND mHparent;
	HWND mHTreeView;
	HWND mHListView;
	int mIDTrewView;
	int mIDListView;

	HFONT hFont;
	HFONT hFontSmall;
	FormStatisticalLogic* myHandle;
public:
	FormStatistical();
	
	~FormStatistical();

	HWND FormStatistical::getHandlerListView();

	void createForm(HWND hParent, long idTD, long idLV, HINSTANCE hInst);

	void updateStatistical(map<TCHAR*, vector<Expense*>, MyCompare> listExpense);

	void updateStatisticalByDate(vector<int> lsitMonth, int year);

	void initForm();

	void getExpenseByType();

	void getExpenseByTypeByDate(vector<int> listMonth, int year);

	vector<int> getListYear();

	void loadData();

	void saveData();

	void updateAgain();


	void deleteExpense();

	void modifyExpense(TCHAR* type, TCHAR* content, TCHAR* money);

	vector<TCHAR*> getListAllType();

	bool isClickToChange();
};

