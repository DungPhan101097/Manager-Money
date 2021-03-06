#include "stdafx.h"
#include "FormAddExpense.h"
#include "Expense.h"

#include <iostream>

FormAddExpense::FormAddExpense()
{
	
}

void FormAddExpense::createForm(HWND hParent, long ID, HINSTANCE hInst)
{
	// Khu vuc thiet lap gia tri thuoc tinh.
	InitCommonControls();
	mHParent = hParent;
	mHInst = hInst;
	mID = ID;

	// Khu vuc khoi tao giao dien.
	HFONT hFont = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
	HFONT hFontSmall = CreateFont(17, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");

	HWND handler = CreateWindow(_T("BUTTON"), _T("Thêm chi tiêu mới"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		20, 20, 320, 320, mHParent, NULL, mHInst, NULL);
	SendMessage(handler, WM_SETFONT, WPARAM(hFont), TRUE);

	handler = CreateWindow(_T("STATIC"), _T("Loại chi tiêu"), WS_CHILD | WS_VISIBLE,
		30, 70, 90, 35, mHParent, NULL, mHInst, NULL);
	SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

	mHCombobox = CreateWindow(_T("COMBOBOX"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_TABSTOP,
		130, 70, 180, 200, mHParent,(HMENU)IDC_CBBOX, hInst, NULL);
	SetFocus(mHCombobox);

	handler = CreateWindow(_T("STATIC"), _T("Nội dung"), WS_CHILD | WS_VISIBLE,
		30, 70 + 70, 90, 35, mHParent, NULL, hInst, NULL);
	SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

	mHContent = CreateWindow(_T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
		130, 70 + 70, 180, 35, mHParent, (HMENU)IDC_EDIT_CONTENT, hInst, NULL);
	SendMessage(mHContent, WM_SETFONT, WPARAM(hFontSmall), TRUE);
	
	handler = CreateWindow(_T("STATIC"), _T("Số tiền"), WS_CHILD | WS_VISIBLE | WS_OVERLAPPED,
		30, 70 + 140, 90, 35, mHParent, NULL, hInst, NULL);
	SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

	mHMoney = CreateWindow(_T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
		130, 70 + 140, 180, 35, mHParent, (HMENU)IDC_EDIT_MONEY, hInst, NULL);
	SendMessage(mHMoney, WM_SETFONT, WPARAM(hFontSmall), TRUE);

	handler = CreateWindow(_T("BUTTON"), _T("Thêm"), WS_CHILD | WS_VISIBLE |WS_TABSTOP,
		130, 70 + 210, 90, 35, mHParent, (HMENU)IDC_BTN_ADD, hInst, NULL);
	SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

	//Khu vuc thiet lap ket noi voi tang logic.
	myHandler = new FormAddExpenseLogic(this);
}

FormAddExpense::~FormAddExpense()
{
}


TCHAR* FormAddExpense::getCurType()
{
	TCHAR* curType = new TCHAR[MAX_LEN];
	int index = SendMessage(mHCombobox, CB_GETCURSEL, 0, 0);
	SendMessage(mHCombobox, CB_GETLBTEXT, index, (LPARAM)curType);

	return curType;
}

TCHAR* FormAddExpense::getCurContent()
{
	TCHAR* curContent = new TCHAR[MAX_LEN];
	GetWindowText(mHContent, curContent, MAX_LEN);
	return curContent;
}

TCHAR* FormAddExpense::getCurMoney()
{
	TCHAR* curMoney = new TCHAR[MAX_LEN];
	GetWindowText(mHMoney, curMoney, MAX_LEN);
	return curMoney;
}

int FormAddExpense::getMonth()
{
	TCHAR* curMonth = new TCHAR[MAX_LEN];
	GetWindowText(mHMonth, curMonth, MAX_LEN);
	int month = _wtoi(curMonth);
	delete[] curMonth;
	return month;
}

int FormAddExpense::getYear()
{
	TCHAR* curMonth = new TCHAR[MAX_LEN];
	GetWindowText(mHYear, curMonth, MAX_LEN);
	int month = _wtoi(curMonth);
	delete[] curMonth;
	return month;
}

void FormAddExpense::addExpense(TCHAR* type, TCHAR* name, TCHAR* money)
{
	try {
		myHandler->addExpense(type, name, money);
	}
	catch (NullComponentException& e0)
	{
		MessageBox(0, L"Bạn không được bỏ trống mục Nội dung hoặc mục Số tiền!", L"Error", MB_OK);
		return;
	}
	catch (CastedStringToNumberException& e1)
	{
		MessageBox(0, L"Bạn chỉ được nhập số tiền là sô nguyên!", L"Error", MB_OK);
		return;
	}
	catch (NegativeNumberException& e2)
	{
		MessageBox(0, L"Số tiền phải là số nguyên > 0!", L"Error", MB_OK);
		return;
	}
	catch (OverloadNumberException& e3)
	{
		TCHAR* noti = new TCHAR[MAX_LEN];
		StrCpy(noti, _T("Số tiền lớn nhất bạn có thể nhập là: "));
		TCHAR* tmpBuf = new TCHAR[RADIX + 1];
		_itow(INT_MAX, tmpBuf, RADIX);
		StrCat(noti, tmpBuf);
		MessageBox(0, noti, L"Error", MB_OK);
		
		delete[] tmpBuf;
		delete[] noti;

		return;
	}
}


void FormAddExpense::initAllTypeCallBack(vector<TCHAR*> listType)
{
	for (int i = 0; i < listType.size(); i++)
	{
		SendMessage(mHCombobox, CB_ADDSTRING, 0, (LPARAM)listType[i]);

	}
	SendMessage(mHCombobox, CB_SETCURSEL, 0, 0);
	HFONT hFontSmall = CreateFont(17, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
	SendMessage(mHCombobox, WM_SETFONT, WPARAM(hFontSmall), TRUE);
}

void FormAddExpense::initAllType()
{
	myHandler->initAllType();
}

