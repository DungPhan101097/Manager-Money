#pragma once
#include "Observer.h"
#include "UpdateFormCircleChartCallBack.h"

class FormCircleChartLogic : public Observer
{
private:
	UpdateFormCircleChartCallBack* mCallBack;

public:
	FormCircleChartLogic(UpdateFormCircleChartCallBack* callBack);
	
	~FormCircleChartLogic();

	void update(map<TCHAR*, vector<Expense*>, MyCompare> listExpense);

	int calTotalCost(vector<Expense*> listEx);

	vector<pair<TCHAR*, float>> watchListExpenseByMonth(vector<int> listMonth, int year);

	vector<pair<TCHAR*, float>> getListPercent();

	vector<pair<TCHAR*, float>> getListPercentByDate(vector<int> listMonth, int year);

	bool isExist(vector<int> curVector, int curInt);

	int calTotalMoney();

	int calTotalMoneyByDate(vector<int> listMonth, int year);
};

