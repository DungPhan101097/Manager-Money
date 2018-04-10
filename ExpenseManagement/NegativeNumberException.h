#pragma once
#include <exception>

using namespace std;

class NegativeNumberException :public exception
{
public:
	NegativeNumberException();

	~NegativeNumberException();

	static void checkNegativeNumber(long long number);
};

