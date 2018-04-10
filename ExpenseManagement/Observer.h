#pragma once
#include <map>
#include <string>
#include <vector>
#include "Expense.h"
#include "DefineHeader.h"

using namespace std;

class Observer
{
public:
	virtual void update(map<TCHAR*, vector<Expense*>, MyCompare> listExpense) = 0;


};

