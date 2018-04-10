#pragma once
#include <map>
#include <vector>
#include "resource.h"
#include "Expense.h"
#include "DefineHeader.h"

class UpdateStatisticalCallBack
{
public:
	virtual void updateStatistical(map<TCHAR*, vector<Expense*>, MyCompare> listExpense) = 0;
};