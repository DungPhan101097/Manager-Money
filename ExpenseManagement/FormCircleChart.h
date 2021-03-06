#pragma once
#include "FormCircleChartLogic.h"
#include "UpdateFormCircleChartCallBack.h"

//Dùng để sử dụng hàm StrCpy, StrNCat
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")

using namespace Gdiplus;

#define LEN_WIDTH 3
#define CANH_HV 270
#define X_PIE_CHART 400
#define Y_PIE_CHART 50
#define MAX_LEN_PERCENT 3
#define RADIX 10

class FormCircleChart : public UpdateFormCircleChartCallBack
{
private:
	HINSTANCE mHinst;
	HWND mHparent;
	int mID;
	HWND mHTotalCost;
	GdiplusStartupInput mGdiplusStartupInput;
	ULONG_PTR mToken;

	FormCircleChartLogic* myHandler;

public:
	FormCircleChart();
	
	~FormCircleChart();

	void createForm(HWND hParent, long ID, HINSTANCE hInst);

	void updateCircleChart(vector<pair<TCHAR*, float>> listPercen);

	void initPieChart();

	void watchListExpenseByMonth(vector<int> listMonth, int year);

	void updateCircleChartByDate(vector<int> lsitMonth, int year);

	void updateAgain();
};

