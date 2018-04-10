#pragma once
#include <ostream>
#include <exception>
#include <limits>
#include <string.h>
#include <sstream>

using namespace std;

class OverloadNumberException : public exception
{
public:
	OverloadNumberException();

	~OverloadNumberException();

	static void checkOverloadedNumber(long long );
};

