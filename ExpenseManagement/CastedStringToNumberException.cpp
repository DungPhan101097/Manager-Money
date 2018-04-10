#include "stdafx.h"
#include "CastedStringToNumberException.h"


CastedStringToNumberException::CastedStringToNumberException()
{
}


CastedStringToNumberException::~CastedStringToNumberException()
{
}

long long CastedStringToNumberException::cast(WCHAR* number) {
	long long result = 0;
	bool flagDot = false;
	int i = 0;

	if (number[i] == '-') {
		i++;
	}

	for (i ; number[i] != '\0' ; i++) {
		if (number[i] <'0' || number[i] >'9') {
			throw CastedStringToNumberException();	
		}
	}
	result = _wtoi64(number);
	return result;
}