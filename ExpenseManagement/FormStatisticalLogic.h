#pragma once
#include "Observer.h"
#include "UpdateFormStatisticalCallBack.h"
#include <ctime>

using namespace std;

class FormStatisticalLogic: public Observer
{
private:
	UpdateStatisticalCallBack* mCallBack;

public:
	FormStatisticalLogic(UpdateStatisticalCallBack* callBack);
	
	~FormStatisticalLogic();

	void update(map<TCHAR*, vector<Expense*>, MyCompare> listExpense);

	vector<TCHAR*> getAllType();

	vector<Expense*> getExpenseByType(TCHAR* type);

	vector<Expense*> getAllExpense();

	vector<int> getListYear();

	void loadData();

	void saveData();

	bool isExist(vector<int> curVector, int curInt);

	vector<Expense*> getExpenseByDate(vector<int> listMonth, int year);

	vector<Expense*> getExpenseByTypeByDate(TCHAR* type, vector<int> listMonth, int year);

	void deleteExpense(TCHAR* content, TCHAR* money, TCHAR* date);

	void modifyExpense(TCHAR* oldContent, TCHAR* oldMoney, TCHAR* oldDate, 
		TCHAR* type, TCHAR* content, TCHAR* money);

};

