#include "stdafx.h"
#include "FormStatisticalLogic.h"
#include "ExpenseManagement.h"
#include "DefineHeader.h"

FormStatisticalLogic::FormStatisticalLogic(UpdateStatisticalCallBack* callBack)
{
	mCallBack = callBack;
	ExpenseManagement::getInstance()->registerObserver(this);
}

FormStatisticalLogic::~FormStatisticalLogic()
{

}

void FormStatisticalLogic::update(map<TCHAR*, vector<Expense*>, MyCompare> listExpense)
{
	mCallBack->updateStatistical(listExpense);
}

vector<TCHAR*> FormStatisticalLogic::getAllType()
{
	vector<TCHAR*> listTypes = ExpenseManagement::getInstance()->getAllTypeExpense();
	return listTypes;
}

vector<Expense*> FormStatisticalLogic::getExpenseByType(TCHAR* type)
{
	return ExpenseManagement::getInstance()->queryExpenseByType(type);
}

vector<Expense*> FormStatisticalLogic::getAllExpense()
{
	return ExpenseManagement::getInstance()->queryAllExpense();
}

vector<int> FormStatisticalLogic::getListYear()
{
	return ExpenseManagement::getInstance()->getListYear();
}

void FormStatisticalLogic::loadData()
{
	ExpenseManagement::getInstance()->initData();
}

void FormStatisticalLogic::saveData()
{
	ExpenseManagement::getInstance()->saveData();
}

bool FormStatisticalLogic::isExist(vector<int> curVector, int curInt)
{
	for (int i = 0; i < curVector.size(); i++)
	{
		if (curVector[i] == curInt)
		{
			return true;
		}
	}
	return false;
}

vector<Expense*> FormStatisticalLogic::getExpenseByDate(vector<int> listMonth, int year)
{
	vector<Expense*> listExpense = ExpenseManagement::getInstance()->queryAllExpense();
	vector<Expense*> listRequire;

	for (int i = 0; i < listExpense.size(); i++)
	{
		if (isExist(listMonth, listExpense[i]->getMonth()) && year == listExpense[i]->getYear())
		{
			listRequire.push_back(listExpense[i]);
		}
	}

	return listRequire;
}


vector<Expense*> FormStatisticalLogic::getExpenseByTypeByDate(TCHAR* type, vector<int> listMonth, int year)
{
	vector<Expense*> listExpense = ExpenseManagement::getInstance()->queryExpenseByType(type);
	vector<Expense*> listRequire;

	for (int i = 0; i < listExpense.size(); i++)
	{
		if (isExist(listMonth, listExpense[i]->getMonth()) && year == listExpense[i]->getYear())
		{
			listRequire.push_back(listExpense[i]);
		}
	}

	return listRequire;
}

void FormStatisticalLogic::deleteExpense(TCHAR* content, TCHAR* money, TCHAR* date)
{
	ExpenseManagement::getInstance()->deleteExpense(content, money, date);
}

void FormStatisticalLogic::modifyExpense(TCHAR* oldContent, TCHAR* oldMoney, TCHAR* oldDate,
	TCHAR* type, TCHAR* content, TCHAR* money)
{
	int nMoney = _wtoi(money);
	time_t now = time(0);
	struct tm* timeNow = localtime(&now);
	Expense* newExpense = new Expense(type, content, nMoney, timeNow->tm_mday, timeNow->tm_mon + 1,
		timeNow->tm_year + 1900);

	ExpenseManagement::getInstance()->modifyExpense(oldContent, oldMoney, oldDate, newExpense);
}
