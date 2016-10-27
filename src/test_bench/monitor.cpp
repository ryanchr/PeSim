/*
*  minitor.cpp
*
*  A monitor model for monitor the PE and driver
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-19 10:41:35 Created.
*
*  Description: The implementation of the monitor model. 
*
*/
#include "frame_app.h"
#include "monitor.h"

void Monitor::main()
{
	if(clk)
	{
		cout << "********************************************************" << endl;
		cout << "Moniter at time "<< sc_time_stamp() << endl;
		cout << "	a = " << a 
			<< "	b = " << b 
			<< "	c = " << c 
			<< "	d = " << d << endl;
		cout << "	e = " << peout_e 
			<< "	s = " << peout_s
			<< "	w = " << peout_w
			<< "	n = " << peout_n << endl;
	}
}