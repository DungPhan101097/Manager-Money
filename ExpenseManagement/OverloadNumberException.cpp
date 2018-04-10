#include "stdafx.h"
#include "OverloadNumberException.h"


OverloadNumberException::OverloadNumberException()
{
}


OverloadNumberException::~OverloadNumberException()
{
}

void OverloadNumberException::checkOverloadedNumber(long long number) {
	if (number >= INT_MAX) {
		throw OverloadNumberException();
	}
}