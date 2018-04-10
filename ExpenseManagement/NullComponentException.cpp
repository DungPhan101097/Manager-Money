#include "stdafx.h"
#include "NullComponentException.h"


NullComponentException::NullComponentException()
{
}


NullComponentException::~NullComponentException()
{
}

void NullComponentException::checkNullComponent(TCHAR* content)
{
	if (StrCmp(content, _T("")) == 0)
	{
		throw NullComponentException();
	}
}
