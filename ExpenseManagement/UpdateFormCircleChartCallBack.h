#pragma once

class UpdateFormCircleChartCallBack
{
public:
	virtual void updateCircleChart(vector<pair<TCHAR*, float>> listPercent) = 0;
};
