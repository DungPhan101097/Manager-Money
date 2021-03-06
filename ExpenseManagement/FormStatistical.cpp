#include "stdafx.h"
#include "FormStatistical.h"
#include <iostream>

FormStatistical::FormStatistical()
{

}


FormStatistical::~FormStatistical()
{
}

void FormStatistical::loadData()
{
	 myHandle->loadData();
	
}

void FormStatistical::saveData()
{
	myHandle->saveData();
}

void FormStatistical::updateStatistical(map<TCHAR*, vector<Expense*>, MyCompare> listExpense)
{
	ListView_DeleteAllItems(mHListView);
	map<TCHAR*, vector<Expense*>, MyCompare>::iterator it;

	LVITEM lv;
	
	vector<Expense*> tmpExpenses;

	for(it = listExpense.begin(); it != listExpense.end(); it++)
	{
		tmpExpenses = it->second;
		for(int i = 0; i< tmpExpenses.size(); i++)
		{
			TCHAR* buffer = new TCHAR[MAX_LEN_MONEY];
			TCHAR* date = new TCHAR[MAX_LEN_MONEY + 2];

			lv.mask = LVIF_TEXT;
			lv.iItem = i;
			lv.iSubItem = 0;
			lv.pszText = tmpExpenses[i]->getContent();
			lv.lParam = (LPARAM)tmpExpenses[i]->getContent();
			ListView_InsertItem(mHListView, &lv);

			lv.iSubItem = 1;
			_itow_s(tmpExpenses[i]->getMoney(), buffer, 11, RADIX);
			lv.pszText = buffer;
			lv.lParam = (LPARAM)buffer;
			ListView_SetItem(mHListView, &lv);

			lv.iSubItem = 2;
			lv.pszText = tmpExpenses[i]->getDate();
			lv.lParam = (LPARAM)tmpExpenses[i]->getDate();
			ListView_SetItem(mHListView, &lv);
		}
	}
}

void FormStatistical::updateStatisticalByDate(vector<int> listMonth, int year)
{
	vector<Expense*> listExpense = myHandle->getExpenseByDate(listMonth, year);
	ListView_DeleteAllItems(mHListView);
	LVITEM lv;
	TCHAR* buffer = new TCHAR[MAX_LEN_MONEY];
	
	for (int i = 0; i < listExpense.size(); i++)
	{
			lv.mask = LVIF_TEXT | LVIF_IMAGE;
			lv.iItem = i;
			lv.iSubItem = 0;
			lv.pszText = listExpense[i]->getContent();
			ListView_InsertItem(mHListView, &lv);

			lv.iSubItem = 1;
			_itow_s(listExpense[i]->getMoney(), buffer, 11, RADIX);
			lv.pszText = buffer;
			ListView_SetItem(mHListView, &lv);

			lv.iSubItem = 2;
			lv.pszText = listExpense[i]->getDate();
			ListView_SetItem(mHListView, &lv);
		
	}
}


void FormStatistical::createForm(HWND hParent, long IDTreeView, long IDListView, HINSTANCE hInst)
{
	// Khu vuc thiet lap gia tri thuoc tinh.
	InitCommonControls();
	mHparent = hParent;
	mIDTrewView = IDTreeView;
	mIDListView = IDListView;
	mHinst = hInst;

	// Khu vuc khoi tao giao dien.
	hFont = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
	hFontSmall = CreateFont(17, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");

	HWND handler = CreateWindow(_T("BUTTON"), _T("Danh sách chi tiêu"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		20, 370, 910, 270,
		mHparent, NULL, hInst, NULL);
	SendMessage(handler, WM_SETFONT, WPARAM(hFont), TRUE);
	mHTreeView = CreateWindowEx(NULL, WC_TREEVIEW, _T("TREE VIEW"), WS_CHILD | WS_VISIBLE |WS_SIZEBOX|
		WS_VSCROLL | WS_HSCROLL | WS_TABSTOP, 30, 400, 310, 220, mHparent, (HMENU)mIDTrewView, hInst, NULL);
	
	// Tam thoi la de nhin thay, sau nay set thanh ko thay.
	mHListView = CreateWindowEx(NULL, WC_LISTVIEW, _T("LIST VIEW"), WS_CHILD | WS_VISIBLE | WS_BORDER |
		WS_VSCROLL | WS_HSCROLL | WS_TABSTOP | WS_SIZEBOX | LVS_REPORT , 
		370, 400, 540, 220, mHparent, (HMENU)mIDListView, hInst, NULL);
	ListView_SetExtendedListViewStyle(mHListView, LVS_EX_GRIDLINES);

	// Khu vuc thuc hien ket noi voi tang logic.
	myHandle = new FormStatisticalLogic(this);
}

void FormStatistical::initForm()
{
	vector<TCHAR*> listTypes = myHandle->getAllType();
	// Khu vuc khoi tao tree view. 
	HIMAGELIST hImageList = ImageList_Create(16, 16, ILC_COLOR16, 1, 1);

	HBITMAP    hbmBlobs = (HBITMAP)LoadImage(mHinst, MAKEINTRESOURCE(IDI_FOOD), IMAGE_ICON, 16, 16, 0);

	ImageList_Add(hImageList, hbmBlobs, NULL);
	
	//DeleteObject(hbmBlobs);
	TreeView_SetImageList(mHTreeView, hImageList, TVSIL_NORMAL);
	//ImageList_Destroy(hImageList);

	TV_INSERTSTRUCT tv;
	tv.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM | TVIF_CHILDREN;
	tv.hParent = NULL;
	tv.item.pszText = _T("Tất cả");
	tv.item.iImage = 0;
	tv.item.lParam = (LPARAM)(_T("All"));
	tv.item.cChildren = 1;

	TreeView_InsertItem(mHTreeView, &tv);
	SendMessage(mHTreeView, WM_SETFONT, (WPARAM)hFontSmall, TRUE);

	for (int i = 0; i< listTypes.size(); i++)
	{
		TV_INSERTSTRUCT tv;
		tv.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM | TVIF_CHILDREN;
		tv.hParent = NULL;
		tv.item.pszText = listTypes[i];
		tv.item.lParam = (LPARAM)(listTypes[i]);
		tv.item.cChildren = 1;
		TreeView_InsertItem(mHTreeView, &tv);
	}
	

	// KHu vuc khoi tao list view.
	RECT rect;
	GetWindowRect(mHListView, &rect);

	LVCOLUMN lvContent;
	lvContent.mask = LVCF_TEXT | LVCF_WIDTH;
	lvContent.fmt = LVCFMT_LEFT;
	lvContent.cx = (rect.right - rect.left) * 0.5;
	lvContent.pszText = _T("Nội dung");
	ListView_InsertColumn(mHListView, 0, &lvContent);
	SendMessage(mHListView, WM_SETFONT, (WPARAM)hFontSmall, TRUE);

	LVCOLUMN lvMoney;
	lvMoney.mask = LVCF_TEXT | LVCF_WIDTH;
	lvMoney.fmt = LVCFMT_LEFT;
	lvMoney.cx = (rect.right - rect.left) * 0.2;
	lvMoney.pszText = _T("Số tiền");
	ListView_InsertColumn(mHListView, 1, &lvMoney);
	

	lvMoney.cx = (rect.right - rect.left) * 0.3;
	lvMoney.pszText = _T("Ngày thêm");
	ListView_InsertColumn(mHListView, 2, &lvMoney);
}

HWND FormStatistical::getHandlerListView()
{
	return mHListView;
}

void FormStatistical::getExpenseByType()
{
	HTREEITEM curSelected = TreeView_GetSelection(mHTreeView);
	TCHAR* pszText = new TCHAR[MAX_LEN];

	TVITEMEX tv;
	tv.mask = TVIF_TEXT;
	tv.cchTextMax = MAX_LEN;
	tv.pszText = pszText;
	tv.hItem = curSelected;
	TreeView_GetItem(mHTreeView, &tv);
	TCHAR* text = (TCHAR*)tv.pszText;

	ListView_DeleteAllItems(mHListView);
	LVITEM lv;
	TCHAR* buffer = new TCHAR[MAX_LEN_MONEY];
	vector<Expense*> tmpExpenses;

	if (StrCmp(text, _T("Tất cả")) == 0)
	{
		tmpExpenses = myHandle->getAllExpense();
	}
	else
	{
		tmpExpenses = myHandle->getExpenseByType(text);
	}

	for (int i = 0; i < tmpExpenses.size(); i++)
	{
		lv.mask = LVIF_TEXT | LVIF_IMAGE;
		lv.iItem = i;
		lv.iSubItem = 0;
		lv.pszText = tmpExpenses[i]->getContent();
		ListView_InsertItem(mHListView, &lv);

		lv.iSubItem = 1;
		_itow_s(tmpExpenses[i]->getMoney(), buffer, 11, RADIX);
		lv.pszText = buffer;
		ListView_SetItem(mHListView, &lv);

		lv.iSubItem = 2;
		lv.pszText = tmpExpenses[i]->getDate();
		ListView_SetItem(mHListView, &lv);
	}
}

void FormStatistical::getExpenseByTypeByDate(vector<int> listMonth, int year)
{
	HTREEITEM curSelected = TreeView_GetSelection(mHTreeView);
	TCHAR* pszText = new TCHAR[MAX_LEN];

	TVITEMEX tv;
	tv.mask = TVIF_TEXT;
	tv.cchTextMax = MAX_LEN;
	tv.pszText = pszText;
	tv.hItem = curSelected;
	TreeView_GetItem(mHTreeView, &tv);
	TCHAR* text = (TCHAR*)tv.pszText;

	ListView_DeleteAllItems(mHListView);
	LVITEM lv;
	TCHAR* buffer = new TCHAR[MAX_LEN_MONEY];
	vector<Expense*> tmpExpenses;

	if (StrCmp(text, _T("Tất cả")) == 0)
	{
		tmpExpenses = myHandle->getExpenseByDate(listMonth, year);
	}
	else
	{
		tmpExpenses = myHandle->getExpenseByTypeByDate(text, listMonth, year);
	}

	for (int i = 0; i < tmpExpenses.size(); i++)
	{
		lv.mask = LVIF_TEXT | LVIF_IMAGE;
		lv.iItem = i;
		lv.iSubItem = 0;
		lv.pszText = tmpExpenses[i]->getContent();
		ListView_InsertItem(mHListView, &lv);

		lv.iSubItem = 1;
		_itow_s(tmpExpenses[i]->getMoney(), buffer, 11, RADIX);
		lv.pszText = buffer;
		ListView_SetItem(mHListView, &lv);

		lv.iSubItem = 2;
		lv.pszText = tmpExpenses[i]->getDate();
		ListView_SetItem(mHListView, &lv);
	}
}



vector<int> FormStatistical::getListYear()
{
	return myHandle->getListYear();
}

void FormStatistical::updateAgain()
{
	vector<Expense*> listAllExpense = myHandle->getAllExpense();
	
	ListView_DeleteAllItems(mHListView);
	LVITEM lv;
	TCHAR* buffer = new TCHAR[MAX_LEN_MONEY];

	for (int i = 0; i < listAllExpense.size(); i++)
	{
		lv.mask = LVIF_TEXT | LVIF_IMAGE;
		lv.iItem = i;
		lv.iSubItem = 0;
		lv.pszText = listAllExpense[i]->getContent();
		ListView_InsertItem(mHListView, &lv);

		lv.iSubItem = 1;
		_itow_s(listAllExpense[i]->getMoney(), buffer, 11, RADIX);
		lv.pszText = buffer;
		ListView_SetItem(mHListView, &lv);

		lv.iSubItem = 2;
		lv.pszText = listAllExpense[i]->getDate();
		ListView_SetItem(mHListView, &lv);
	}
}

void FormStatistical::deleteExpense()
{
	// Xac dinh expense nao can xoa.
	int pos = ListView_GetSelectionMark(mHListView);
	TCHAR* content = new TCHAR[MAX_LEN];
	TCHAR* date = new TCHAR[MAX_LEN];
	TCHAR* money = new TCHAR[MAX_LEN];

	if (pos != -1)
	{
		ListView_GetItemText(mHListView, pos, 0, content, MAX_LEN);
		ListView_GetItemText(mHListView, pos, 1, money, MAX_LEN);
		ListView_GetItemText(mHListView, pos, 2, date, MAX_LEN);

		ListView_DeleteItem(mHListView, pos);

	}
	// Xoa
	myHandle->deleteExpense(content, money, date);
}

void FormStatistical::modifyExpense(TCHAR* type, TCHAR* content, TCHAR* money)
{
	// Xac dinh expense nao can xoa.
	int pos = ListView_GetSelectionMark(mHListView);
	TCHAR* mcontent = new TCHAR[MAX_LEN];
	TCHAR* mdate = new TCHAR[MAX_LEN];
	TCHAR* mmoney = new TCHAR[MAX_LEN];

	if (pos != -1)
	{
		ListView_GetItemText(mHListView, pos, 0, mcontent, MAX_LEN);
		ListView_GetItemText(mHListView, pos, 1, mmoney, MAX_LEN);
		ListView_GetItemText(mHListView, pos, 2, mdate, MAX_LEN);

		ListView_DeleteItem(mHListView, pos);
	}
	// Xoa
	myHandle->modifyExpense(mcontent, mmoney, mdate, type, content, money);
}

vector<TCHAR*> FormStatistical::getListAllType()
{
	return myHandle->getAllType();
}

bool FormStatistical::isClickToChange()
{
	int pos = ListView_GetSelectionMark(mHListView);;
	return pos == -1 ? false : true;
}


