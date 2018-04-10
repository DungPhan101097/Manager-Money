#include "stdafx.h"
#include "NegativeNumberException.h"


NegativeNumberException::NegativeNumberException()
{
}


NegativeNumberException::~NegativeNumberException()
{
}

void NegativeNumberException::checkNegativeNumber(long long number) {
	if (number < 0) {
		throw NegativeNumberException();
	}
}
