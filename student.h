#pragma once
#include "user.h"
#include <Windows.h>
class student :
	public user
{
public:
	student();
	~student();
	void GameTime(string nm);
	
};

