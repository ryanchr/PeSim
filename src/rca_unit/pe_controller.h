/*
*  pe_controller.h
*
*  A controller model for fetching data to the PE array
*
*  Copyright (C) 2010  Ren Chen
*
*  2010-3-31 22:52:15 Created.
*
*  Description: The definition of the pe_controller model. 
*
*/
//The model structure looks like this:
/////////////////////////////// 
//.______________________.
//|  pe_controller             |     
//|                    clk         |<----
//|           cfg_enable       |---->
//|           cfg_finish         |<-----
//|          output_finish     |---->
//|                a<32>        |---->
//|                b<32>        |---->
//|                c<32>        |---->
//|                d<32>        |---->
//.______________________.
///////////////////////////////
#ifndef PE_CONTROLLER_H
#define PE_CONTROLLER_H

#include "frame_app.h"
#include "Bus_non_blocking_if.h"
#include "pe_cfgmem.h"

class PE_Controller: public sc_module
{
public:
	sc_in_clk clk;
	sc_in<bool>   cfg_finish;
	sc_out<bool> output_finish;
	sc_out<bool> cfg_enable;
	sc_out<sc_int<32> > a, b, c, d;
	sc_port<Bus_non_blocking_if> bus_master_port3;    //read input data of pe by bus	
	
	void main();
	void signal_generate();
	void signal_fetch(Uint32 address, Uint32 * data);
	
	SC_HAS_PROCESS(PE_Controller);
	PE_Controller(sc_module_name name
		,Uint32 _unique_priority) 
		: sc_module(name)
		,unique_priority(_unique_priority)
	{
		//SC_THREAD(main);             //fetch input data of pe after configuration accomplilshed
		//sensitive << cfg_finish;
		SC_THREAD(signal_generate);           //generate config enable signal
		sensitive << clk.pos()<<cfg_finish;
	}

	~PE_Controller();
private:
	Uint32 unique_priority;
};

#endif