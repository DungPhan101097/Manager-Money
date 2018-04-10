#pragma once

#include "Observable.h"
#include "Expense.h"
#include "DefineHeader.h"
#include <fstream>
#include <locale>
#include <codecvt>
#include <atlconv.h>


class ExpenseManagement : public Observable
{
private:
	map<TCHAR*, vector<Expense*>, MyCompare> listExpense;

	static ExpenseManagement* instance ;


private:
	ExpenseManagement();

	~ExpenseManagement();

public:
	static ExpenseManagement* getInstance();

	void initData();

	void saveData();

	void addExpense(Expense* expense);

	vector<TCHAR*> getAllTypeExpense();

	vector<Expense*> queryExpenseByType(TCHAR* type);

	vector<Expense*> queryAllExpense();

	vector<Expense*> getExpensesByMonth(vector<int> listMonth, int year);

	vector<int> getListYear();

	bool isExist(vector<int> curVector, int curInt);

	void deleteExpense(TCHAR* content, TCHAR* money, TCHAR* date);

	void modifyExpense(TCHAR* oldContent, TCHAR* oldMoney, TCHAR* oldDate, Expense* newExpense);

};

