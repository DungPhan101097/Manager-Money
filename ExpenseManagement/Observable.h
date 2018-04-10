#pragma once

#include <vector>
#include "Observer.h"

using namespace std;

class Observable
{
protected:
	vector<Observer*> listObserver;

public:
	Observable();

	~Observable();
	void registerObserver(Observer* obs);

	void removenObserver(Observer* obs);

};

