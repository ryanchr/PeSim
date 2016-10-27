/*
*  topsystem.h
*
*  top level module
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-12-3 20:58:43 Created.
*
*  Description: This file mainly instantiate the PE unit. 
*
*/
#include "topsystem.h"

void Topsys::SimPause()
{
	controler->SimPause();
}

void Topsys::SimContinue()
{
	controler->SimContinue();
}

void Topsys::MainIdle()
{
	bool flag = true;
	while (_flag_pause)
	{
		if (flag)
		{
			flag = false;
			cout << "top simulatio paused" << endl;
		}
	}
}