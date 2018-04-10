#pragma once
#include <exception>

using namespace std;

class CastedStringToNumberException :public exception 
{
public:
	
public:
	CastedStringToNumberException();

	~CastedStringToNumberException();

	static long long cast(WCHAR* number);
};

