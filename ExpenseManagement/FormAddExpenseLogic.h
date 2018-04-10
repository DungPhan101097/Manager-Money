#pragma once

#include <ctime>

#include "UpdateFormAddCallBack.h"
#include "NegativeNumberException.h"
#include "OverloadNumberException.h"
#include "CastedStringToNumberException.h"
#include "NullComponentException.h"



class FormAddExpenseLogic 
{
private:
	UpdateFormAddCallback* mCallBack;
public:
	FormAddExpenseLogic(UpdateFormAddCallback* callBack);
	
	~FormAddExpenseLogic();
	
	void addExpense(TCHAR* type, TCHAR* name, TCHAR* money);

	void initAllType();

};

