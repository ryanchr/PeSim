/*
*  driver.cpp
*
*  A driver model for test and verify the PE array
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-19 9:24:15 Created.
*
*  Description: The implementation of the driver model. 
*
*/
#include "frame_app.h"
#include <time.h>
#include <stdlib.h>
#include "driver.h"

void Driver::config()
{
	/*Generate the configuration signal*/
    	#if 0
	while(1)
	{

		cfg_data = 0x48040000;   /*in: east, north; out: east; function: add*/
		cfg_enable = 1;
		cout << "config start at time " << sc_time_stamp() << endl;
		wait(1, SC_NS);
		cfg_enable = 0;
		wait(19, SC_NS);

		cfg_data = 0x12080000;	/*in: west, south; out: north; function: add*/
		cfg_enable = 1;
		cout << "config start at time " << sc_time_stamp() << endl;
		wait(1, SC_NS);
		cfg_enable = 0;
		wait(19, SC_NS);

		cfg_data = 0x48010001;	/*in: north, east; out: south; function: sub*/
		cfg_enable = 1;
		cout << "config start at time " << sc_time_stamp() << endl;
		wait(1, SC_NS);
		cfg_enable = 0;
		wait(19, SC_NS);
	}
	#endif
}

void Driver::main()
{
	/*Generate the data*/
	srand((int)time(0));	/*for rand() a random a data*/
	while(1)
	{
		a = 1+(int)(10.0*rand()/(RAND_MAX+1.0));
		b = 1+(int)(10.0*rand()/(RAND_MAX+1.0));
		c = 1+(int)(10.0*rand()/(RAND_MAX+1.0));
		d = 1+(int)(10.0*rand()/(RAND_MAX+1.0));
		wait();
	}
}