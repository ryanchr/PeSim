/*
*  minitor.h
*
*  A monitor model for monitor the PE and driver
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-19 10:41:35 Created.
*
*  Description: The definition of the monitor model. 
*
*/
//The Monitor structure looks like this:
/////////////////////////////////////////
//       .______________________.
//       |  Monitor             |     
//  ---->| clk      peout_e<32> |<----
//  ---->| a<32>    peout_w<32> |<----
//  ---->| b<32>    peout_n<32> |<----
//  ---->| c<32>    peout_s<32> |<----
//  ---->| d<32>                |<----
//       .______________________.
/////////////////////////////////////////

#ifndef ME_MONITOR_H
#define ME_MONITOR_H

class Monitor : public sc_module
{
public:
	sc_in_clk clk;
	sc_in<sc_int<32> > a, b, c, d;
	sc_in<sc_int<32> > peout_e, peout_w, peout_n, peout_s;

	void main();

	SC_HAS_PROCESS(Monitor);
	Monitor(sc_module_name name) : sc_module(name)
	{
		SC_METHOD(main);
		sensitive << clk;
	}
};

#endif