#include "stdafx.h"
#include "Observable.h"



Observable::Observable()
{

}

Observable::~Observable()
{

}

void Observable::registerObserver(Observer* obs)
{
	listObserver.push_back(obs);
}

void Observable::removenObserver(Observer* obs)
{
	for (int i = 0; i < listObserver.size(); i++)
	{
		if (listObserver[i] == obs)
		{
			listObserver.erase(listObserver.begin() + i);
			break;
		}
	}
}
