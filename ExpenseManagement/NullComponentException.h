#pragma once

#include <exception>
//Dùng để sử dụng hàm StrCpy, StrNCat
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

using namespace std;

class NullComponentException : public exception
{
public:
	NullComponentException();

	~NullComponentException();

	static void checkNullComponent(TCHAR* content);
};

