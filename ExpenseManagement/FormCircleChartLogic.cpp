#include "stdafx.h"
#include "FormCircleChartLogic.h"
#include "ExpenseManagement.h"

FormCircleChartLogic::FormCircleChartLogic(UpdateFormCircleChartCallBack* callBack)
{
	mCallBack = callBack;
	ExpenseManagement::getInstance()->registerObserver(this);
}


FormCircleChartLogic::~FormCircleChartLogic()
{
}

void FormCircleChartLogic::update(map<TCHAR*, vector<Expense*>, MyCompare> listExpense)
{
	vector<pair<TCHAR*, float>> listPercent;
	map<TCHAR*, vector<Expense*>, MyCompare>::iterator it;
	int totalCost = 0;
	float percent;

	for (it = listExpense.begin(); it != listExpense.end(); it++)
	{
		totalCost += calTotalCost(it->second);
	}

	for (it = listExpense.begin(); it != listExpense.end(); it++)
	{
		pair<TCHAR*, float> tmpPair;
		tmpPair.first = it->first;
		tmpPair.second = ((float)calTotalCost(it->second) / totalCost )* 100;
		listPercent.push_back(tmpPair);
	}

	mCallBack->updateCircleChart(listPercent);
}

int FormCircleChartLogic::calTotalCost(vector<Expense*> listEx)
{
	int total = 0;
	for (int i = 0; i < listEx.size(); i++)
	{
		total += listEx[i]->getMoney();
	}
	return total;
}

vector<pair<TCHAR*, float>> FormCircleChartLogic::watchListExpenseByMonth(vector<int> listMonth, int year)
{
	vector<Expense*> listExpenseRequire = ExpenseManagement::getInstance()->getExpensesByMonth(listMonth, year);
	vector<pair<TCHAR*, float>> listPercent;
	
	return listPercent;
}

vector<pair<TCHAR*, float>> FormCircleChartLogic::getListPercent()
{
	vector<Expense*> listAllExpense = ExpenseManagement::getInstance()->queryAllExpense();
	vector<pair<TCHAR*, float>> listPercent;

	int totalCost =  calTotalCost(listAllExpense);
	map<TCHAR*, vector<Expense*>, MyCompare> listExpenseByType;
	
	for (int i = 0; i < listAllExpense.size(); i++)
	{
		listExpenseByType[listAllExpense[i]->getType()].push_back(listAllExpense[i]);
	}

	map<TCHAR*, vector<Expense*>, MyCompare>::iterator it;
	for (it = listExpenseByType.begin(); it != listExpenseByType.end(); it++)
	{
		pair<TCHAR*, float> tmpPair;
		tmpPair.first = it->first;
		tmpPair.second = ((float)calTotalCost(it->second) / totalCost) * 100;
		listPercent.push_back(tmpPair);
	}

	return listPercent;
}

vector<pair<TCHAR*, float>> FormCircleChartLogic::getListPercentByDate(vector<int> listMonth, int year)
{
	vector<Expense*> listAllExpense = ExpenseManagement::getInstance()->queryAllExpense();
	vector<Expense*> listRequirer;
	for (int i = 0; i < listAllExpense.size(); i++)
	{
		if (isExist(listMonth, listAllExpense[i]->getMonth()) && year == listAllExpense[i]->getYear())
		{
			listRequirer.push_back(listAllExpense[i]);
		}
	}
	vector<pair<TCHAR*, float>> listPercent;

	int totalCost = calTotalCost(listRequirer);
	map<TCHAR*, vector<Expense*>, MyCompare> listExpenseByType;

	for (int i = 0; i < listRequirer.size(); i++)
	{
		listExpenseByType[listRequirer[i]->getType()].push_back(listRequirer[i]);
	}

	map<TCHAR*, vector<Expense*>, MyCompare>::iterator it;
	for (it = listExpenseByType.begin(); it != listExpenseByType.end(); it++)
	{
		pair<TCHAR*, float> tmpPair;
		tmpPair.first = it->first;
		tmpPair.second = ((float)calTotalCost(it->second) / totalCost) * 100;
		listPercent.push_back(tmpPair);
	}

	return listPercent;
}

int FormCircleChartLogic::calTotalMoneyByDate(vector<int> listMonth, int year)
{
	vector<Expense*> listAllExpense = ExpenseManagement::getInstance()->queryAllExpense();
	vector<Expense*> listRequirer;
	for (int i = 0; i < listAllExpense.size(); i++)
	{
		if (isExist(listMonth, listAllExpense[i]->getMonth()) && year == listAllExpense[i]->getYear())
		{
			listRequirer.push_back(listAllExpense[i]);
		}
	}
	return calTotalCost(listRequirer);
}

bool FormCircleChartLogic::isExist(vector<int> curVector, int curInt)
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

int FormCircleChartLogic::calTotalMoney()
{
	vector<Expense*> listAllExpense = ExpenseManagement::getInstance()->queryAllExpense();
	vector<pair<TCHAR*, float>> listPercent;

	return  calTotalCost(listAllExpense);
}
