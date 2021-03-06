#include "stdafx.h"
#include "FormCircleChart.h"
#include <iostream>

FormCircleChart::FormCircleChart()
{
}


void FormCircleChart::createForm(HWND hParent, long ID, HINSTANCE hInst)
{
	// Khu vuc thiet lap gia tri thuoc tinh.
	InitCommonControls();
	mHparent = hParent;
	mID = ID;
	mHinst = hInst;

	// Khu vuc khoi tao giao dien.
	HFONT hFont = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
	HWND handler = CreateWindow(_T("BUTTON"), _T("Thông tin thống kê"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		380, 20, 550, 320, mHparent, NULL, hInst, NULL);
	SendMessage(handler, WM_SETFONT, WPARAM(hFont), TRUE);

	handler = CreateWindow(_T("STATIC"), _T("Tổng tiền"), WS_CHILD | WS_VISIBLE ,
		710, 305, 70, 25, mHparent, NULL, hInst, NULL);
	SendMessage(handler, WM_SETFONT, WPARAM(hFont), TRUE);

	mHTotalCost = CreateWindow(_T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER,
		790, 300, 120, 30, mHparent, NULL, hInst, NULL);
	SendMessage(mHTotalCost, WM_SETFONT, WPARAM(hFont), TRUE);
	
	// Khu vuc khoi tao ket noi voi lop logic.
	myHandler = new FormCircleChartLogic(this);

}


FormCircleChart::~FormCircleChart()
{
 	

}

void FormCircleChart::initPieChart()
{
	vector<pair<TCHAR*, float>> listPercent = myHandler->getListPercent();
	
	//Day la cho ve hinh tron.
	HDC hdc = GetDC(mHparent);
	Graphics* graphic = new Graphics(hdc);
	Pen* pen = new Pen(Color(128, 128, 0), LEN_WIDTH);

	Gdiplus::Rect rectCircle = { X_PIE_CHART, Y_PIE_CHART, CANH_HV, CANH_HV };
	graphic->SetSmoothingMode(SmoothingModeAntiAlias);
	SolidBrush* brushText = new SolidBrush(Color(255, 255, 255));
	SolidBrush* brushTextNote = new SolidBrush(Color(0, 0, 0));

	// Day la cho ve chu thich
	SolidBrush* brushEat = new SolidBrush(Color(255, 0, 0));
	SolidBrush* brushMove = new SolidBrush(Color(0, 128, 0));
	SolidBrush* brushHouse = new SolidBrush(Color(255, 128, 192));
	SolidBrush* brushVerhicle = new SolidBrush(Color(0, 0, 128));
	SolidBrush* brushEssentialItem = new SolidBrush(Color(128, 64, 0));
	SolidBrush* brushService = new SolidBrush(Color(255, 128, 0));
	Font font(&FontFamily(L"Arial"), 11);

	Gdiplus::Rect rectNote = { 750, 50, 50, 25 };
	graphic->FillRectangle(brushEat, rectNote);
	rectNote = { 750, 90, 50, 25 };
	graphic->FillRectangle(brushMove, rectNote);
	rectNote = { 750, 130, 50, 25 };
	graphic->FillRectangle(brushHouse, rectNote);
	rectNote = { 750, 170, 50, 25 };
	graphic->FillRectangle(brushVerhicle, rectNote);
	rectNote = { 750, 210, 50, 25 };
	graphic->FillRectangle(brushEssentialItem, rectNote);
	rectNote = { 750, 250, 50, 25 };
	graphic->FillRectangle(brushService, rectNote);
	
	graphic->DrawString(_T("Ăn uống"), -1, &font, PointF(810, 55), &StringFormat(0, 0), brushTextNote);
	graphic->DrawString(_T("Di chuyển"), -1, &font, PointF(810, 95), &StringFormat(0, 0), brushTextNote);
	graphic->DrawString(_T("Nhà cửa"), -1, &font, PointF(810, 135), &StringFormat(0, 0), brushTextNote);
	graphic->DrawString(_T("Xe cộ"), -1, &font, PointF(810, 175), &StringFormat(0, 0), brushTextNote);
	graphic->DrawString(_T("Nhu yếu phẩm"), -1, &font, PointF(810, 215), &StringFormat(0, 0), brushTextNote);
	graphic->DrawString(_T("Dịch vụ"), -1, &font, PointF(810, 255), &StringFormat(0, 0), brushTextNote);

	if (listPercent.size() == 0)
	{
		SolidBrush* brush1 = new SolidBrush(Color(255, 255, 255));
		graphic->DrawEllipse(pen, rectCircle);
		graphic->FillPie(brush1, rectCircle, -90, 360);
		delete brush1;
	}
	else
	{
		float curAngle = -90;
		int totalPercent = 0;
		vector<pair<TCHAR*, int>> listIntPercent;
		for (int i = 0; i < listPercent.size() - 1; i++)
		{
			pair<TCHAR*, int> tmp = make_pair(listPercent[i].first, (int)listPercent[i].second);
			listIntPercent.push_back(tmp);
			totalPercent += (int)listPercent[i].second;
		}
		pair<TCHAR*, int> tmp = make_pair(listPercent[listPercent.size() - 1].first, 100 - totalPercent);
		listIntPercent.push_back(tmp);

		TCHAR* buffer = new TCHAR[MAX_LEN_PERCENT];
		Gdiplus::Rect rectNote;

		// Cap nhat hinh tron va chu thich.
		graphic->DrawEllipse(pen, rectCircle);
		for (int i = 0; i < listPercent.size(); i++)
		{
			if (StrCmp(listPercent[i].first, _T("Ăn uống")) == 0)
			{
				rectNote = { 750, 50, 50, 25 };
				graphic->FillRectangle(brushEat, rectNote);
				graphic->FillPie(brushEat, rectCircle, curAngle, listPercent[i].second * 3.6);
				curAngle += listPercent[i].second * 3.6;
				_itow_s(listIntPercent[i].second, buffer, MAX_LEN_PERCENT + 1, RADIX);
				StrCat(buffer, _T("%"));
				graphic->DrawString(buffer, -1, &font, PointF(756, 55), &StringFormat(0, 0), brushText);

			}
			else if (StrCmp(listPercent[i].first, _T("Di chuyển")) == 0)
			{
				rectNote = { 750, 90, 50, 25 };
				graphic->FillRectangle(brushMove, rectNote);
				graphic->FillPie(brushMove, rectCircle, curAngle, listPercent[i].second * 3.6);
				curAngle += listPercent[i].second * 3.6;
				_itow_s(listIntPercent[i].second, buffer, MAX_LEN_PERCENT + 1, RADIX);
				StrCat(buffer, _T("%"));
				graphic->DrawString(buffer, -1, &font, PointF(756, 95), &StringFormat(0, 0), brushText);
			}
			else if (StrCmp(listPercent[i].first, _T("Nhà cửa")) == 0)
			{
				rectNote = { 750, 130, 50, 25 };
				graphic->FillRectangle(brushHouse, rectNote);
				graphic->FillPie(brushHouse, rectCircle, curAngle, listPercent[i].second * 3.6);
				curAngle += listPercent[i].second * 3.6;
				_itow_s(listIntPercent[i].second, buffer, MAX_LEN_PERCENT + 1, RADIX);
				StrCat(buffer, _T("%"));
				graphic->DrawString(buffer, -1, &font, PointF(756, 135), &StringFormat(0, 0), brushText);
			}
			else if (StrCmp(listPercent[i].first, _T("Xe cộ")) == 0)
			{
				rectNote = { 750, 170, 50, 25 };
				graphic->FillRectangle(brushVerhicle, rectNote);
				graphic->FillPie(brushVerhicle, rectCircle, curAngle, listPercent[i].second * 3.6);
				curAngle += listPercent[i].second * 3.6;
				_itow_s(listIntPercent[i].second, buffer, MAX_LEN_PERCENT + 1, RADIX);
				StrCat(buffer, _T("%"));
				graphic->DrawString(buffer, -1, &font, PointF(756, 175), &StringFormat(0, 0), brushText);
			}
			else if (StrCmp(listPercent[i].first, _T("Nhu yếu phẩm")) == 0)
			{
				rectNote = { 750, 210, 50, 25 };
				graphic->FillRectangle(brushEssentialItem, rectNote);
				graphic->FillPie(brushEssentialItem, rectCircle, curAngle, listPercent[i].second * 3.6);
				curAngle += listPercent[i].second * 3.6;
				_itow_s(listIntPercent[i].second, buffer, MAX_LEN_PERCENT + 1, RADIX);
				StrCat(buffer, _T("%"));
				graphic->DrawString(buffer, -1, &font, PointF(756, 215), &StringFormat(0, 0), brushText);
			}
			else if (StrCmp(listPercent[i].first, _T("Dịch vụ")) == 0)
			{
				rectNote = { 750, 250, 50, 25 };
				graphic->FillRectangle(brushService, rectNote);
				graphic->FillPie(brushService, rectCircle, curAngle, listPercent[i].second * 3.6);
				curAngle += listPercent[i].second * 3.6;
				_itow_s(listIntPercent[i].second, buffer, MAX_LEN_PERCENT + 1, RADIX);
				StrCat(buffer, _T("%"));
				graphic->DrawString(buffer, -1, &font, PointF(756, 255), &StringFormat(0, 0), brushText);
			}
		}


	}

	delete brushText;
	
	delete brushEat;
	delete brushEssentialItem;
	delete brushHouse;
	delete brushMove;
	delete brushService;
	delete brushVerhicle;
	delete pen;
	delete graphic;
}


void FormCircleChart::updateCircleChart(vector<pair<TCHAR*, float>> listPercen)
{
	// Tinh tong tien.
	
	int totalMoney = myHandler->calTotalMoney();
	TCHAR* sTotalCost = new TCHAR[RADIX + 1];
	_itow(totalMoney, sTotalCost, RADIX);
	SetWindowText(mHTotalCost, sTotalCost);

	// Tinh mang chua phan tram dang so nguyen.
	vector<pair<TCHAR*, int>> listIntPercent;
	int totalPercent = 0;
	if (listPercen.size() > 0)
	{
		for (int i = 0; i < listPercen.size() - 1; i++)
		{
			pair<TCHAR*, int> tmp = make_pair(listPercen[i].first, (int)listPercen[i].second);
			listIntPercent.push_back(tmp);
			totalPercent += (int)listPercen[i].second;
		}
		pair<TCHAR*, int> tmp = make_pair(listPercen[listPercen.size() - 1].first, 100 - totalPercent);
		listIntPercent.push_back(tmp);
	}
	int index = 0;
	float curAngle = -90;

	HDC hdc = GetDC(mHparent);
	Graphics* graphic = new Graphics(hdc);
	Pen* pen = new Pen(Color(128, 128, 0), LEN_WIDTH);
	Gdiplus::Rect rectCircle = { X_PIE_CHART, Y_PIE_CHART, CANH_HV, CANH_HV };
	graphic->SetSmoothingMode(SmoothingModeAntiAlias);

	SolidBrush* brushEat = new SolidBrush(Color(255, 0, 0));
	SolidBrush* brushMove = new SolidBrush(Color(0, 128, 0));
	SolidBrush* brushHouse = new SolidBrush(Color(255, 128, 192));
	SolidBrush* brushVerhicle = new SolidBrush(Color(0, 0, 128));
	SolidBrush* brushEssentialItem = new SolidBrush(Color(128, 64, 0));
	SolidBrush* brushService = new SolidBrush(Color(255, 128, 0));
	Font font(&FontFamily(L"Arial"), 11);
	SolidBrush* brushText = new SolidBrush(Color(255, 255, 255));
	TCHAR* buffer = new TCHAR[MAX_LEN_PERCENT];
	Gdiplus::Rect rectNote;

	// Cap nhat hinh tron va chu thich.
	graphic->DrawEllipse(pen, rectCircle);
	if (listPercen.size() == 0)
	{
		SolidBrush* brushBk = new SolidBrush(Color(255, 255, 255));
		graphic->DrawEllipse(pen, rectCircle);
		graphic->FillPie(brushBk, rectCircle, curAngle, 360);

		Gdiplus::Rect rectNote = { 750, 50, 50, 25 };
		graphic->FillRectangle(brushEat, rectNote);
		rectNote = { 750, 90, 50, 25 };
		graphic->FillRectangle(brushMove, rectNote);
		rectNote = { 750, 130, 50, 25 };
		graphic->FillRectangle(brushHouse, rectNote);
		rectNote = { 750, 170, 50, 25 };
		graphic->FillRectangle(brushVerhicle, rectNote);
		rectNote = { 750, 210, 50, 25 };
		graphic->FillRectangle(brushEssentialItem, rectNote);
		rectNote = { 750, 250, 50, 25 };
		graphic->FillRectangle(brushService, rectNote);

		delete brushBk;
	}
	else {
		rectNote = { 750, 50, 50, 25 };
		graphic->FillRectangle(brushEat, rectNote);
		StrCpy(buffer, _T("0%"));
		graphic->DrawString(buffer, -1, &font, PointF(756, 55), &StringFormat(0, 0), brushText);
		
		rectNote = { 750, 90, 50, 25 };
		graphic->FillRectangle(brushMove, rectNote);
		graphic->DrawString(buffer, -1, &font, PointF(756, 95), &StringFormat(0, 0), brushText);
		
		rectNote = { 750, 130, 50, 25 };
		graphic->FillRectangle(brushHouse, rectNote);
		graphic->DrawString(buffer, -1, &font, PointF(756, 135), &StringFormat(0, 0), brushText);
		
		rectNote = { 750, 170, 50, 25 };
		graphic->FillRectangle(brushVerhicle, rectNote);
		graphic->DrawString(buffer, -1, &font, PointF(756, 175), &StringFormat(0, 0), brushText);
		
		rectNote = { 750, 210, 50, 25 };
		graphic->FillRectangle(brushEssentialItem, rectNote);
		graphic->DrawString(buffer, -1, &font, PointF(756, 215), &StringFormat(0, 0), brushText);
		
		rectNote = { 750, 250, 50, 25 };
		graphic->FillRectangle(brushService, rectNote);
		graphic->DrawString(buffer, -1, &font, PointF(756, 255), &StringFormat(0, 0), brushText);


		for (int i = 0; i < listPercen.size(); i++)
		{
			if (StrCmp(listPercen[i].first, _T("Ăn uống")) == 0)
			{
				rectNote = { 750, 50, 50, 25 };
				graphic->FillRectangle(brushEat, rectNote);
				graphic->FillPie(brushEat, rectCircle, curAngle, listPercen[i].second * 3.6);
				curAngle += listPercen[i].second * 3.6;
				_itow_s(listIntPercent[i].second, buffer, MAX_LEN_PERCENT + 1, RADIX);
				StrCat(buffer, _T("%"));
				graphic->DrawString(buffer, -1, &font, PointF(756, 55), &StringFormat(0, 0), brushText);

			}
			else if (StrCmp(listPercen[i].first, _T("Di chuyển")) == 0)
			{
				rectNote = { 750, 90, 50, 25 };
				graphic->FillRectangle(brushMove, rectNote);
				graphic->FillPie(brushMove, rectCircle, curAngle, listPercen[i].second * 3.6);
				curAngle += listPercen[i].second * 3.6;
				_itow_s(listIntPercent[i].second, buffer, MAX_LEN_PERCENT + 1, RADIX);
				StrCat(buffer, _T("%"));
				graphic->DrawString(buffer, -1, &font, PointF(756, 95), &StringFormat(0, 0), brushText);
			}
			else if (StrCmp(listPercen[i].first, _T("Nhà cửa")) == 0)
			{
				rectNote = { 750, 130, 50, 25 };
				graphic->FillRectangle(brushHouse, rectNote);
				graphic->FillPie(brushHouse, rectCircle, curAngle, listPercen[i].second * 3.6);
				curAngle += listPercen[i].second * 3.6;
				_itow_s(listIntPercent[i].second, buffer, MAX_LEN_PERCENT + 1, RADIX);
				StrCat(buffer, _T("%"));
				graphic->DrawString(buffer, -1, &font, PointF(756, 135), &StringFormat(0, 0), brushText);
			}
			else if (StrCmp(listPercen[i].first, _T("Xe cộ")) == 0)
			{
				rectNote = { 750, 170, 50, 25 };
				graphic->FillRectangle(brushVerhicle, rectNote);
				graphic->FillPie(brushVerhicle, rectCircle, curAngle, listPercen[i].second * 3.6);
				curAngle += listPercen[i].second * 3.6;
				_itow_s(listIntPercent[i].second, buffer, MAX_LEN_PERCENT + 1, RADIX);
				StrCat(buffer, _T("%"));
				graphic->DrawString(buffer, -1, &font, PointF(756, 175), &StringFormat(0, 0), brushText);
			}
			else if (StrCmp(listPercen[i].first, _T("Nhu yếu phẩm")) == 0)
			{
				rectNote = { 750, 210, 50, 25 };
				graphic->FillRectangle(brushEssentialItem, rectNote);
				graphic->FillPie(brushEssentialItem, rectCircle, curAngle, listPercen[i].second * 3.6);
				curAngle += listPercen[i].second * 3.6;
				_itow_s(listIntPercent[i].second, buffer, MAX_LEN_PERCENT + 1, RADIX);
				StrCat(buffer, _T("%"));
				graphic->DrawString(buffer, -1, &font, PointF(756, 215), &StringFormat(0, 0), brushText);
			}
			else if (StrCmp(listPercen[i].first, _T("Dịch vụ")) == 0)
			{
				rectNote = { 750, 250, 50, 25 };
				graphic->FillRectangle(brushService, rectNote);
				graphic->FillPie(brushService, rectCircle, curAngle, listPercen[i].second * 3.6);
				curAngle += listPercen[i].second * 3.6;
				_itow_s(listIntPercent[i].second, buffer, MAX_LEN_PERCENT + 1, RADIX);
				StrCat(buffer, _T("%"));
				graphic->DrawString(buffer, -1, &font, PointF(756, 255), &StringFormat(0, 0), brushText);
			}
		}
	}
	//delete buffer;
	delete brushText;
	delete brushEat;
	delete brushEssentialItem;
	delete brushHouse;
	delete brushMove;
	delete brushService;
	delete brushVerhicle;
	delete pen;
	delete graphic;
}

void FormCircleChart::updateCircleChartByDate(vector<int> listMonth, int year)
{
	vector<pair<TCHAR*, float>> listPercent = myHandler->getListPercentByDate(listMonth, year);
	
	updateCircleChart(listPercent);
	int totalMoney = myHandler->calTotalMoneyByDate(listMonth, year);
	TCHAR* sTotalCost = new TCHAR[RADIX + 1];
	_itow(totalMoney, sTotalCost, RADIX);
	SetWindowText(mHTotalCost, sTotalCost);

}


void FormCircleChart::watchListExpenseByMonth(vector<int> listMonth, int year)
{
	vector<pair<TCHAR*, float>> listPercent = myHandler->watchListExpenseByMonth(listMonth, year);

	updateCircleChart(listPercent);

}

void FormCircleChart::updateAgain()
{
	vector<pair<TCHAR*, float>> listPercent = myHandler->getListPercent();
	updateCircleChart(listPercent);
}
