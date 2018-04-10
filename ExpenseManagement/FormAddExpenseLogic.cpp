#include "stdafx.h"
#include "FormAddExpenseLogic.h"
#include "UpdateFormAddCallBack.h"
#include "ExpenseManagement.h"

FormAddExpenseLogic::FormAddExpenseLogic(UpdateFormAddCallback* callBack)
{
	mCallBack = callBack;
}

FormAddExpenseLogic::~FormAddExpenseLogic()
{

}

void FormAddExpenseLogic::addExpense(TCHAR* type, TCHAR* name, TCHAR* money)
{
	time_t now = time(0);
	struct tm* timeNow = localtime(&now);
	long long nMoney = 0;

	try {
		NullComponentException::checkNullComponent(name);
		NullComponentException::checkNullComponent(money);
		nMoney = CastedStringToNumberException::cast(money);
		NegativeNumberException::checkNegativeNumber(nMoney);
		OverloadNumberException::checkOverloadedNumber(nMoney);
	}
	catch (NullComponentException& e0)
	{
		throw e0;
	}
	catch (CastedStringToNumberException& e1)
	{
		throw e1;
	}
	catch (NegativeNumberException& e2)
	{
		throw e2;
	}
	catch (OverloadNumberException& e3)
	{
		throw e3;
	}

	ExpenseManagement::getInstance()->addExpense(new Expense(type, name, nMoney, timeNow->tm_mday, timeNow->tm_mon + 1,
		timeNow->tm_year + 1900));
}



void FormAddExpenseLogic::initAllType()
{
	vector<TCHAR*> listTypes = ExpenseManagement::getInstance()->getAllTypeExpense();

	mCallBack->initAllTypeCallBack(listTypes);
}