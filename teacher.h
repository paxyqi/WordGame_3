#pragma once
#include "user.h"
class teacher :
	public user
{
public:
	teacher();
	~teacher();
	void AddWord(string nm);
};

