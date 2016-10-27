/*
*  control.h
*
*  For test, not used!
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-19 9:24:15 Created.
*
*  Description: No use. 
*
*/

#ifndef ME_CONTROLER_H
#define ME_CONTROLER_H

#include "frame_app.h"

class Controler : sc_module
{
public:
	sc_in<bool> clk;

	void MainIdle();

	void SimPause();
	void SimContinue();
	Uint64 SimCycles();
	SC_HAS_PROCESS(Controler);
	Controler(sc_module_name name) : sc_module(name)
	{
		SC_METHOD(MainIdle);
		sensitive << clk.pos();
		_counter = 0;
		_flag_pause = false;
	}

private:
	bool _flag_pause;
	Uint64 _counter; 
};

#endif
