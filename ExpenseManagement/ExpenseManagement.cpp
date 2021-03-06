#include "stdafx.h"
#include "ExpenseManagement.h"

ExpenseManagement* ExpenseManagement::instance = NULL;

ExpenseManagement::ExpenseManagement()
{
	
}


ExpenseManagement::~ExpenseManagement()
{
}


void ExpenseManagement::initData()
{
	// Nap tat ca cac chi tieu tu file dung.txt vao listExpense.
	HANDLE hFile = CreateFile(_T("./dung.txt"), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE) {
		DWORD dwFileSize = GetFileSize(hFile, NULL);
		if (dwFileSize != 0) {
			LPSTR pszFileText;
			pszFileText = (LPSTR)GlobalAlloc(GPTR, dwFileSize + 1);
			if (pszFileText != NULL)
			{
				DWORD dwRead;
				if (ReadFile(hFile, pszFileText, dwFileSize, &dwRead, NULL))
				{
					int wchars_num = MultiByteToWideChar(CP_UTF8, 0, pszFileText, -1, NULL, 0);
					wchar_t* wstr = new wchar_t[wchars_num];
					MultiByteToWideChar(CP_UTF8, 0, pszFileText, -1, wstr, wchars_num);
					
					std::wstring wFromFile(wstr);
					int offset = 0;
					while ((offset = wFromFile.find_first_of(L'\r')) != -1) {
						wFromFile.erase(offset, 2);
						wstring wstype = wFromFile.substr(0, offset);
						TCHAR* type = new TCHAR[offset + 1];
						StrCpy(type, (wchar_t *)wstype.c_str());
						wFromFile.erase(0, offset);

						offset = wFromFile.find_first_of(L'\r');
						wFromFile.erase(offset, 2);
						wstring wsContent = wFromFile.substr(0, offset);
						TCHAR* content = new TCHAR[offset + 1];
						StrCpy(content, (wchar_t *)wsContent.c_str());
						wFromFile.erase(0, offset);

						offset = wFromFile.find_first_of(L'\r');
						wFromFile.erase(offset, 2);
						wstring wsMoney = wFromFile.substr(0, offset);
						TCHAR* sMoney = (wchar_t *)wsMoney.c_str();
						int money = _wtoi(sMoney);
						wFromFile.erase(0, offset);

						offset = wFromFile.find_first_of(L'/');
						wFromFile.erase(offset, 1);
						wstring wsDay = wFromFile.substr(0, offset);
						TCHAR* sday = (wchar_t *)wsDay.c_str();
						int day = _wtoi(sday);
						wFromFile.erase(0, offset);

						offset = wFromFile.find_first_of(L'/');
						wFromFile.erase(offset, 1);
						wstring wsMonth = wFromFile.substr(0, offset);
						TCHAR* sMonth = (wchar_t *)wsMonth.c_str();
						int month = _wtoi(sMonth);
						wFromFile.erase(0, offset);

						offset = wFromFile.find_first_of(L'\r');
						int year;
						TCHAR* sYear;
						if (offset > 0)
						{
							wFromFile.erase(offset, 2);
							wstring tmp = wFromFile.substr(0, offset);
							sYear = (wchar_t *)tmp.c_str();
							year = _wtoi(sYear);
							wFromFile.erase(0, offset);
						}
						else {
							sYear = (wchar_t *)wFromFile.c_str();
							year = _wtoi(sYear);
						}
						Expense* newExpense = new Expense(type, content, money, day, month, year);
						listExpense[type].push_back(newExpense);
					}
					for (int i = 0; i < listObserver.size(); i++)
					{
						listObserver[i]->update(listExpense);
					}
				}
			}
		}
		CloseHandle(hFile);
	}

	
}

void ExpenseManagement::saveData()
{
	bool flag = false;
	std::wofstream fileOut("./dung.txt");
	fileOut.imbue(std::locale(fileOut.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	// Nap tat ca chi tieu tu listExpense vao file dung.txt
	
	map<TCHAR*, vector<Expense*>, MyCompare>::iterator it;
	for (it = listExpense.begin(); it != listExpense.end(); it++)
	{
		for (int i = 0; i < it->second.size(); i++)
		{
			if (flag)
				fileOut << '\n';
			std::wstring str = std::wstring(it->second[i]->getType());
			fileOut << str << '\n';
			str = std::wstring(it->second[i]->getContent());
			fileOut << str << '\n';
			TCHAR* buffer = new TCHAR[RADIX];
			_itow(it->second[i]->getMoney(), buffer, RADIX);
			str = std::wstring(buffer);
			fileOut << str << '\n';
			_itow(it->second[i]->getDay(), buffer, RADIX);
			str = std::wstring(buffer);
			fileOut << str << '/';
			_itow(it->second[i]->getMonth(), buffer, RADIX);
			str = std::wstring(buffer);
			fileOut << str << '/';
			_itow(it->second[i]->getYear(), buffer, RADIX);
			str = std::wstring(buffer);
			fileOut << str;
			flag = true;
		}
	}

	fileOut.close();
}


vector<TCHAR*> ExpenseManagement::getAllTypeExpense()
{
	vector<TCHAR*> listTypes;

	listTypes.push_back(_T("Ăn uống"));
	listTypes.push_back(_T("Di chuyển"));
	listTypes.push_back(_T("Nhà cửa"));
	listTypes.push_back(_T("Xe cộ"));
	listTypes.push_back(_T("Nhu yếu phẩm"));
	listTypes.push_back(_T("Dịch vụ"));

	return listTypes;
}

ExpenseManagement* ExpenseManagement::getInstance()
{
	if (instance == NULL)
		instance = new ExpenseManagement();
	return instance;
}

void ExpenseManagement::addExpense(Expense* expense)
{
	listExpense[expense->getType()].push_back(expense);
	for (int i = 0; i < listObserver.size(); i++)
	{
		listObserver[i]->update(listExpense);
	}
}

vector<Expense*> ExpenseManagement::queryExpenseByType(TCHAR* type)
{
	return listExpense[type];
}

vector<Expense*> ExpenseManagement::queryAllExpense()
{
	vector<Expense*> listTotal;
	map<TCHAR*, vector<Expense*>, MyCompare>::iterator it;
	for (it = listExpense.begin(); it != listExpense.end(); it++)
	{
		listTotal.insert(listTotal.end(), it->second.begin(), it->second.end());
	}

	return listTotal;
}

vector<Expense*> ExpenseManagement::getExpensesByMonth(vector<int> listMonth, int year)
{
	vector<Expense*> listEx;
	map<TCHAR*, vector<Expense*>, MyCompare>::iterator it;
	for (it = listExpense.begin(); it != listExpense.end(); it++)
	{
		for (int i = 0; i < it->second.size(); i++)
		{
			if (it->second[i]->getYear() == year && isExist(listMonth, it->second[i]->getMonth()))
			{
				listEx.push_back(it->second[i]);
			}
		}
	}
	
	return listEx;
}


vector<int> ExpenseManagement::getListYear()
{
	vector<int> listYear;
	map<TCHAR*, vector<Expense*>, MyCompare>::iterator it;
	
	for (it = listExpense.begin(); it != listExpense.end(); it++)
	{
		for (int i = 0; i < it->second.size(); i++)
		{
			if (isExist(listYear, it->second[i]->getYear()) == 0)
			{
				listYear.push_back(it->second[i]->getYear());
			}
		}
	}

	return listYear;
}


bool ExpenseManagement::isExist(vector<int> curVector, int curInt)
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

void ExpenseManagement::deleteExpense(TCHAR* content, TCHAR* money, TCHAR* date)
{
	int nMoney = _wtoi(money);
	map<TCHAR*, vector<Expense*>, MyCompare>::iterator it;
	for (it = listExpense.begin(); it != listExpense.end(); it++)
	{
		for (int i = 0; i < it->second.size(); i++)
		{
			if (StrCmp(it->second[i]->getContent(), content) == 0 && it->second[i]->getMoney() == nMoney &&
				StrCmp(it->second[i]->getDate(), date) == 0)
			{
				it->second.erase(it->second.begin() + i);
			}
		}
	}
	for (int i = 0; i < listObserver.size(); i++)
	{
		listObserver[i]->update(listExpense);
	}
}

void ExpenseManagement::modifyExpense(TCHAR* oldContent, TCHAR* oldMoney, TCHAR* oldDate, Expense* newExpense)
{
	int nMoney = _wtoi(oldMoney);
	map<TCHAR*, vector<Expense*>, MyCompare>::iterator it;
	for (it = listExpense.begin(); it != listExpense.end(); it++)
	{
		for (int i = 0; i < it->second.size(); i++)
		{
			if (StrCmp(it->second[i]->getContent(), oldContent) == 0 && it->second[i]->getMoney() == nMoney &&
				StrCmp(it->second[i]->getDate(), oldDate) == 0)
			{
				it->second.erase(it->second.begin() + i);
			}
		}
	}

	listExpense[newExpense->getType()].push_back(newExpense);

	for (int i = 0; i < listObserver.size(); i++)
	{
		listObserver[i]->update(listExpense);
	}
}