#pragma once

#include "resource.h"
#include <Windows.h>
#include <windowsx.h>
#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")

#include "FormAddExpense.h"
#include "FormCircleChart.h"
#include "FormStatistical.h"



using namespace Gdiplus;
#define MAX_LEN_YEAR 4 
#define MAX_INT 10
#define RADIX 10

// My global vaariable.
GdiplusStartupInput gGdiplusStartupInput;
ULONG_PTR gToken;
FormAddExpense* gFormAddExpense = NULL;
FormCircleChart* gFormChart = NULL;
FormStatistical* gFormSatistical = NULL;
bool gIsQuering = false;
int gYear = 0;
vector<int> gListMonth;


BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
void OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
void OnPaint(HWND hWnd);
LRESULT OnNotify(HWND hwnd, int idFrom, NMHDR *pnm);
INT_PTR CALLBACK Dialog2_WinProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);