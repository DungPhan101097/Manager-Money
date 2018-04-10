#pragma once

//Dùng để sử dụng hàm StrCpy, StrNCat
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#include <Windows.h>
#include <vector>

using namespace std;

#define RADIX 10

struct MyCompare
{
	bool operator() (const TCHAR* lhs, const TCHAR* rhs) const
	{
		return StrCmp(lhs, rhs) < 0;
	}
};


