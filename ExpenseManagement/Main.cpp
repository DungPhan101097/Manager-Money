// ExpenseManagement.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Main.h"


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hWnd;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_EXPENSEMANAGEMENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EXPENSEMANAGEMENT));

    MSG msg;

    // Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!IsDialogMessage(hWnd, &msg)) {
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EXPENSEMANAGEMENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreatePatternBrush(LoadBitmap(hInstance,
		MAKEINTRESOURCE(IDB_BITMAP2)));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_EXPENSEMANAGEMENT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, 0, 963, 729, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


HBRUSH hbrBkgnd = NULL;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_NOTIFY, OnNotify);
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, RGB(0, 0, 0));
		SetBkColor(hdcStatic, RGB(255, 255, 255));

		if (hbrBkgnd == NULL)
		{
			hbrBkgnd = CreateSolidBrush(RGB(255, 255, 255));
		}
		return (INT_PTR)hbrBkgnd;
	}
	break;
    case WM_DESTROY:
		GdiplusShutdown(gToken);
		gFormSatistical->saveData();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Dialog1_WinProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		HFONT hFontSmall = CreateFont(16, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");

		HWND handler = CreateWindow(_T("STATIC"), _T("XEM DANH SÁCH CHI TIÊU VÀ VẼ BIỂU ĐỒ THEO NGÀY THÁNG"), 
			WS_CHILD | WS_VISIBLE,
			50, 20, 500, 35, hDlg, NULL, hInst, NULL);
		SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

		handler = CreateWindow(_T("STATIC"), _T("Chọn năm"), WS_CHILD | WS_VISIBLE,
			30, 60, 70, 35, hDlg, NULL, hInst, NULL);
		SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

		CreateWindow(_T("COMBOBOX"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_TABSTOP | CBS_SORT,
			120, 55, 180, 200, hDlg, (HMENU)IDC_COMBO1, hInst, NULL);

		handler = CreateWindow(_T("STATIC"), _T("Chọn tháng"), WS_CHILD | WS_VISIBLE,
			30, 100, 70, 35, hDlg, NULL, hInst, NULL);
		SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

		handler = CreateWindow(_T("BUTTON"), _T("Chọn tất cả"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 120, 120, 100, 35,
			hDlg, (HMENU)IDC_CHECK1, hInst, NULL);
		SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

		handler = CreateWindow(_T("BUTTON"), _T("Tháng 1"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 120, 160, 100, 35,
			hDlg, (HMENU)IDC_CHECK2, hInst, NULL);
		SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

		handler = CreateWindow(_T("BUTTON"), _T("Tháng 2"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 120, 200, 100, 35,
			hDlg, (HMENU)IDC_CHECK3, hInst, NULL);
		SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

		handler = CreateWindow(_T("BUTTON"), _T("Tháng 3"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 120, 240, 100, 35,
			hDlg, (HMENU)IDC_CHECK4, hInst, NULL);
		SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

		handler = CreateWindow(_T("BUTTON"), _T("Tháng 4"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 120, 280, 100, 35,
			hDlg, (HMENU)IDC_CHECK5, hInst, NULL);
		SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

		handler = CreateWindow(_T("BUTTON"), _T("Tháng 5"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 120, 320, 100, 35,
			hDlg, (HMENU)IDC_CHECK6, hInst, NULL);
		SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

		handler = CreateWindow(_T("BUTTON"), _T("Tháng 6"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 120, 360, 100, 35,
			hDlg, (HMENU)IDC_CHECK7, hInst, NULL);
		SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

		handler = CreateWindow(_T("BUTTON"), _T("Tháng 7"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 320, 120, 100, 35,
			hDlg, (HMENU)IDC_CHECK8, hInst, NULL);
		SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

		handler = CreateWindow(_T("BUTTON"), _T("Tháng 8"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 320, 160, 100, 35,
			hDlg, (HMENU)IDC_CHECK9, hInst, NULL);
		SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

		handler = CreateWindow(_T("BUTTON"), _T("Tháng 9"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 320, 200, 100, 35,
			hDlg, (HMENU)IDC_CHECK10, hInst, NULL);
		SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

		handler = CreateWindow(_T("BUTTON"), _T("Tháng 10"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 320, 240, 100, 35,
			hDlg, (HMENU)IDC_CHECK11, hInst, NULL);
		SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

		handler = CreateWindow(_T("BUTTON"), _T("Tháng 11"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 320, 280, 100, 35,
			hDlg, (HMENU)IDC_CHECK12, hInst, NULL);
		SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

		handler = CreateWindow(_T("BUTTON"), _T("Tháng 12"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 320, 320, 100, 35,
			hDlg, (HMENU)IDC_CHECK13, hInst, NULL);
		SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);


		TCHAR* buffer = new TCHAR[MAX_LEN_YEAR];
		vector<int> listYear;
		listYear = gFormSatistical->getListYear();
		for (int i = 0; i < listYear.size(); i++)
		{
			TCHAR* buffer = new TCHAR[MAX_INT];
			_itow(listYear[i], buffer, RADIX);
			SendDlgItemMessage(hDlg, IDC_COMBO1, CB_ADDSTRING, 0, (LPARAM)buffer);
		}
		SendDlgItemMessage(hDlg, IDC_COMBO1, CB_SETCURSEL, 0, 0);
		
		
		SendDlgItemMessage(hDlg, IDC_COMBO1, WM_SETFONT, WPARAM(hFontSmall), TRUE);
		return (INT_PTR)TRUE;

	}
	
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_CHECK1:
			if (SendDlgItemMessage(hDlg, IDC_CHECK2, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
			{
				CheckDlgButton(hDlg, IDC_CHECK1, FALSE);
				CheckDlgButton(hDlg, IDC_CHECK2, FALSE);
				CheckDlgButton(hDlg, IDC_CHECK3, FALSE);
				CheckDlgButton(hDlg, IDC_CHECK4, FALSE);
				CheckDlgButton(hDlg, IDC_CHECK5, FALSE);
				CheckDlgButton(hDlg, IDC_CHECK6, FALSE);
				CheckDlgButton(hDlg, IDC_CHECK7, FALSE);
				CheckDlgButton(hDlg, IDC_CHECK8, FALSE);
				CheckDlgButton(hDlg, IDC_CHECK9, FALSE);
				CheckDlgButton(hDlg, IDC_CHECK10, FALSE);
				CheckDlgButton(hDlg, IDC_CHECK11, FALSE);
				CheckDlgButton(hDlg, IDC_CHECK12, FALSE);
				CheckDlgButton(hDlg, IDC_CHECK13, FALSE);
			}
			else
			{
				CheckDlgButton(hDlg, IDC_CHECK1, TRUE);
				CheckDlgButton(hDlg, IDC_CHECK2, TRUE);
				CheckDlgButton(hDlg, IDC_CHECK3, TRUE);
				CheckDlgButton(hDlg, IDC_CHECK4, TRUE);
				CheckDlgButton(hDlg, IDC_CHECK5, TRUE);
				CheckDlgButton(hDlg, IDC_CHECK6, TRUE);
				CheckDlgButton(hDlg, IDC_CHECK7, TRUE);
				CheckDlgButton(hDlg, IDC_CHECK8, TRUE);
				CheckDlgButton(hDlg, IDC_CHECK9, TRUE);
				CheckDlgButton(hDlg, IDC_CHECK10, TRUE);
				CheckDlgButton(hDlg, IDC_CHECK11, TRUE);
				CheckDlgButton(hDlg, IDC_CHECK12, TRUE);
				CheckDlgButton(hDlg, IDC_CHECK13, TRUE);
			}

			break;
		case IDC_CHECK2:
			if (SendDlgItemMessage(hDlg, IDC_CHECK2, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
			{
				CheckDlgButton(hDlg, IDC_CHECK2, FALSE);
			}
			else {
				CheckDlgButton(hDlg, IDC_CHECK2, TRUE);
			}
			break;
		case IDC_CHECK3:
			if (SendDlgItemMessage(hDlg, IDC_CHECK3, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
			{
				CheckDlgButton(hDlg, IDC_CHECK3, FALSE);
			}
			else {
				CheckDlgButton(hDlg, IDC_CHECK3, TRUE);
			}
			break;
		case IDC_CHECK4:
			if (SendDlgItemMessage(hDlg, IDC_CHECK4, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
			{
				CheckDlgButton(hDlg, IDC_CHECK4, FALSE);
			}
			else {
				CheckDlgButton(hDlg, IDC_CHECK4, TRUE);
			}
			break;
		case IDC_CHECK5:
			if (SendDlgItemMessage(hDlg, IDC_CHECK5, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
			{
				CheckDlgButton(hDlg, IDC_CHECK5, FALSE);
			}
			else {
				CheckDlgButton(hDlg, IDC_CHECK5, TRUE);
			}
			break;
		case IDC_CHECK6:
			if (SendDlgItemMessage(hDlg, IDC_CHECK6, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
			{
				CheckDlgButton(hDlg, IDC_CHECK6, FALSE);
			}
			else {
				CheckDlgButton(hDlg, IDC_CHECK6, TRUE);
			}
			break;
		case IDC_CHECK7:
			if (SendDlgItemMessage(hDlg, IDC_CHECK7, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
			{
				CheckDlgButton(hDlg, IDC_CHECK7, FALSE);
			}
			else {
				CheckDlgButton(hDlg, IDC_CHECK7, TRUE);
			}
			break;
		case IDC_CHECK8:
			if (SendDlgItemMessage(hDlg, IDC_CHECK8, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
			{
				CheckDlgButton(hDlg, IDC_CHECK8, FALSE);
			}
			else {
				CheckDlgButton(hDlg, IDC_CHECK8, TRUE);
			}
			break;
		case IDC_CHECK9:
			if (SendDlgItemMessage(hDlg, IDC_CHECK9, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
			{
				CheckDlgButton(hDlg, IDC_CHECK9, FALSE);
			}
			else {
				CheckDlgButton(hDlg, IDC_CHECK9, TRUE);
			}
			break;
		case IDC_CHECK10:
			if (SendDlgItemMessage(hDlg, IDC_CHECK10, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
			{
				CheckDlgButton(hDlg, IDC_CHECK10, FALSE);
			}
			else {
				CheckDlgButton(hDlg, IDC_CHECK10, TRUE);
			}
			break;
		case IDC_CHECK11:
			if (SendDlgItemMessage(hDlg, IDC_CHECK11, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
			{
				CheckDlgButton(hDlg, IDC_CHECK11, FALSE);
			}
			else {
				CheckDlgButton(hDlg, IDC_CHECK11, TRUE);
			}
			break; 
		case IDC_CHECK12:
				if (SendDlgItemMessage(hDlg, IDC_CHECK12, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
				{
					CheckDlgButton(hDlg, IDC_CHECK12, FALSE);
				}
				else {
					CheckDlgButton(hDlg, IDC_CHECK12, TRUE);
				}
				break;
		case IDC_CHECK13:
			if (SendDlgItemMessage(hDlg, IDC_CHECK13, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
			{
				CheckDlgButton(hDlg, IDC_CHECK13, FALSE);
			}
			else {
				CheckDlgButton(hDlg, IDC_CHECK13, TRUE);
			}
			break;
		case IDOK:
		{
			// Lay nam.
			TCHAR* curType = new TCHAR[MAX_LEN];
			int index = SendDlgItemMessage(hDlg, IDC_COMBO1, CB_GETCURSEL, 0, 0);
			SendDlgItemMessage(hDlg, IDC_COMBO1, CB_GETLBTEXT, index, (LPARAM)curType);
			gYear = _wtoi(curType);
			
			gListMonth.clear();
			if (IsDlgButtonChecked(hDlg, IDC_CHECK1))
			{
				for (int i = 1; i < 13; i++)
				{
					gListMonth.push_back(i);
				}
			}
			else
			{
				if (IsDlgButtonChecked(hDlg, IDC_CHECK2))
				{
					gListMonth.push_back(1);
				}
				if (IsDlgButtonChecked(hDlg, IDC_CHECK3))
				{
					gListMonth.push_back(2);
				}
				if (IsDlgButtonChecked(hDlg, IDC_CHECK4))
				{
					gListMonth.push_back(3);
				}
				if (IsDlgButtonChecked(hDlg, IDC_CHECK5))
				{
					gListMonth.push_back(4);
				}
				if (IsDlgButtonChecked(hDlg, IDC_CHECK6))
				{
					gListMonth.push_back(5);
				}
				if (IsDlgButtonChecked(hDlg, IDC_CHECK7))
				{
					gListMonth.push_back(6);
				}
				if (IsDlgButtonChecked(hDlg, IDC_CHECK8))
				{
					gListMonth.push_back(7);
				}
				if (IsDlgButtonChecked(hDlg, IDC_CHECK9))
				{
					gListMonth.push_back(8);
				}
				if (IsDlgButtonChecked(hDlg, IDC_CHECK10))
				{
					gListMonth.push_back(9);
				}
				if (IsDlgButtonChecked(hDlg, IDC_CHECK11))
				{
					gListMonth.push_back(10);
				}
				if (IsDlgButtonChecked(hDlg, IDC_CHECK12))
				{
					gListMonth.push_back(11);
				}
				if (IsDlgButtonChecked(hDlg, IDC_CHECK13))
				{
					gListMonth.push_back(12);
				}
			}

			gFormSatistical->updateStatisticalByDate(gListMonth, gYear);
			gFormChart->updateCircleChartByDate(gListMonth, gYear);
			gIsQuering = true;
			EndDialog(hDlg, TRUE);
			return (INT_PTR)TRUE; 
		}
			break;
		case IDC_BUTTON1:
			EndDialog(hDlg, FALSE);
			return (INT_PTR)TRUE;
			break;
		}
	}
	break;
	}
	return (INT_PTR)FALSE;
}


BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{

	GdiplusStartup(&gToken, &gGdiplusStartupInput, NULL);

	gFormAddExpense = new FormAddExpense();
	gFormAddExpense->createForm(hWnd, IDC_FORM_ADD, hInst);
	gFormAddExpense->initAllType();

	gFormChart = new FormCircleChart();
	gFormChart->createForm(hWnd, IDC_FORM_CHART, hInst);

	gFormSatistical = new FormStatistical();
	gFormSatistical->createForm(hWnd, IDC_TREEVIEW, IDC_LISTVIEW, hInst);
	gFormSatistical->initForm();
	gFormSatistical->loadData();	


	return true;
}

void OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDC_BTN_ADD:
	{
		gIsQuering = false;
		gFormAddExpense->addExpense(gFormAddExpense->getCurType(), gFormAddExpense->getCurContent(), 
			gFormAddExpense->getCurMoney());
		
	}
	break;
	case ID_FILE_OPTIONS:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dialog1_WinProc);
		break;
	
	case ID_FILE_ENDQUERY:
		gIsQuering = false;
		gFormChart->updateAgain();
		gFormSatistical->updateAgain();

		break;

	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;

	case IDM_EXIT:
		
		DestroyWindow(hWnd);
		break;
	}
}

void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	
	if(!gIsQuering)
		gFormChart->initPieChart();

	EndPaint(hWnd, &ps);
}

LRESULT OnNotify(HWND hwnd, int idFrom, NMHDR *pnm)
{
	int nCurSelIndex;
	LPNMTREEVIEW lpnmTreeView = (LPNMTREEVIEW)pnm;
	
	switch (pnm->code)
	{
	case TVN_SELCHANGED:
	{
		if (gIsQuering)
		{
			gFormSatistical->getExpenseByTypeByDate(gListMonth, gYear);

		}
		else
		{
			gFormSatistical->getExpenseByType();
			gFormChart->updateAgain();
		}
	}
	case NM_DBLCLK:
	{
		if (pnm->hwndFrom == gFormSatistical->getHandlerListView())
		{
			if (gFormSatistical->isClickToChange()) {
				int option = MessageBox(0, _T("Bạn có muốn xóa chi tiêu này không? Yes để Xóa/ No để hiệu chỉnh"),
					_T("Notification"),
					MB_YESNOCANCEL | MB_ICONQUESTION);
				if (option == IDYES)
				{
					gFormSatistical->deleteExpense();
				}
				else if (option == IDNO)
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, Dialog2_WinProc);
				}
			}
			
		}
			
	}
	break;
	}
	return 0;
}

INT_PTR CALLBACK Dialog2_WinProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		HFONT hFontSmall = CreateFont(16, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");

		HWND handler = CreateWindow(_T("STATIC"), _T("CHỈNH SỬA CHI TIÊU"),
			WS_CHILD | WS_VISIBLE,
			60, 20, 300, 35, hDlg, NULL, hInst, NULL);
		SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

		handler = CreateWindow(_T("STATIC"), _T("Loại chi tiêu"), WS_CHILD | WS_VISIBLE,
			10, 60, 90, 35, hDlg, NULL, hInst, NULL);
		SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

		CreateWindow(_T("COMBOBOX"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_TABSTOP | CBS_SORT,
			100, 55, 180, 200, hDlg, (HMENU)IDC_COMBO_CHANGE, hInst, NULL);

		handler = CreateWindow(_T("STATIC"), _T("Nội dung"), WS_CHILD | WS_VISIBLE,
			10, 100, 90, 35, hDlg, NULL, hInst, NULL);
		SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

		handler = CreateWindow(_T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER,
			100, 100, 180, 35, hDlg, (HMENU)IDC_CONTENT_CHANGE, hInst, NULL);
		SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

		handler = CreateWindow(_T("STATIC"), _T("Số tiền"), WS_CHILD | WS_VISIBLE,
			10, 140, 90, 35, hDlg, NULL, hInst, NULL);
		SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

		handler = CreateWindow(_T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER,
			100, 140, 180, 35, hDlg, (HMENU)IDC_MONEY_CHANGE, hInst, NULL);
		SendMessage(handler, WM_SETFONT, WPARAM(hFontSmall), TRUE);

		vector<TCHAR*> listAllType = gFormSatistical->getListAllType();

		for (int i = 0; i < listAllType.size(); i++)
		{
			SendDlgItemMessage(hDlg, IDC_COMBO_CHANGE, CB_ADDSTRING, 0, (LPARAM)listAllType[i]);
		}
		SendDlgItemMessage(hDlg, IDC_COMBO_CHANGE, CB_SETCURSEL, 0, 0);
		SendDlgItemMessage(hDlg, IDC_COMBO_CHANGE, WM_SETFONT, WPARAM(hFontSmall), TRUE);

		return (INT_PTR)TRUE;

	}

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		
		case IDOK:
		{
			TCHAR* type = new TCHAR[MAX_LEN];
			TCHAR* money = new TCHAR[MAX_LEN];
			TCHAR* content = new TCHAR[MAX_LEN];
			try {
				int index = SendDlgItemMessage(hDlg, IDC_COMBO_CHANGE, CB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hDlg, IDC_COMBO_CHANGE, CB_GETLBTEXT, index, (LPARAM)type);

				GetDlgItemText(hDlg, IDC_CONTENT_CHANGE, content, MAX_LEN);

				GetDlgItemText(hDlg, IDC_MONEY_CHANGE, money, MAX_LEN);

				NullComponentException::checkNullComponent(money);
				NullComponentException::checkNullComponent(content);
				int nMoney = CastedStringToNumberException::cast(money);
				NegativeNumberException::checkNegativeNumber(nMoney);
				OverloadNumberException::checkOverloadedNumber(nMoney);
			}
			catch (NullComponentException& e0)
			{
				MessageBox(0, L"Bạn không được bỏ trống mục Nội dung hoặc mục Số tiền!", L"Error", MB_OK);
				return (INT_PTR)FALSE;
			}
			catch (CastedStringToNumberException& e1)
			{
				MessageBox(0, L"Bạn chỉ được nhập số tiền là sô nguyên!", L"Error", MB_OK);
				return (INT_PTR)FALSE;
			}
			catch (NegativeNumberException& e2)
			{
				MessageBox(0, L"Số tiền phải là số nguyên > 0!", L"Error", MB_OK);
				return (INT_PTR)FALSE;
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

				return (INT_PTR)FALSE;
			}
			
			gFormSatistical->modifyExpense(type, content, money);

			EndDialog(hDlg, TRUE);
			return (INT_PTR)TRUE;
		}
		break;
		case ID_CANCEL:
			EndDialog(hDlg, FALSE);
			return (INT_PTR)TRUE;
			break;
		}
	}
	break;
	}
	return (INT_PTR)FALSE;
}

