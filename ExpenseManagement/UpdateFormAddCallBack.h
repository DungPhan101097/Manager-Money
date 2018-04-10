#pragma once
#include <vector>
#include <string>
#include "Expense.h"

using namespace std;

class UpdateFormAddCallback
{
public :
	virtual	void initAllTypeCallBack(vector<TCHAR*> listType) = 0;
};