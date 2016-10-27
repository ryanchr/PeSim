/*
*  frame_app.h
*
*  A framework for each module
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-30 10:32:26 Created.
*
*  Description: The definition of the framework of this project. 
*
*/

#ifndef ME_FRAME_APP_H
#define ME_FRAME_APP_H

#include <iostream>
#include <systemc.h>
#include "types.h"
#include "tools.h"

using namespace std;

class FrameApp
{
public:
	FrameApp();
	~FrameApp();
	/***debug operation***/
	//virtual void start_sim() = 0;
	//virtual void pause_sim() = 0;
};

#endif
