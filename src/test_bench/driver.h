/*
*  driver.h
*
*  A driver model for test and verify the PE array
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-19 9:24:15 Created.
*
*  Description: The definition of the driver model. 
*
*/
//The Pe_unit structure looks like this:
/////////////////////////////// 
//.______________________.
//|  Driver              |     
//|                  clk |<----
//|           cfg_enable |---->
//|           g_data<32> |---->
//|                a<32> |---->
//|                b<32> |---->
//|                c<32> |---->
//|                d<32> |---->
//.______________________.
///////////////////////////////
#ifndef ME_DRIVER_H
#define ME_DRIVER_H

class Driver: public sc_module
{
public:
	sc_in_clk clk;
	sc_out<sc_int<32> > a, b, c, d;
	//sc_out<sc_uint<32> > cfg_data;
	//sc_out<bool> cfg_enable;

	void main();
	void config();
	
	SC_HAS_PROCESS(Driver);
	Driver(sc_module_name name) : sc_module(name)
	{
		SC_THREAD(main);
		sensitive << clk.pos();
		//SC_THREAD(config);
	}
};

#endif