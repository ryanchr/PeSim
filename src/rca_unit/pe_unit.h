/*
*  pe_unit.h
*
*  Reconfigurable unit Module interfaces
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-18 10:19:53 Created.
*
*  Description: This file mainly defines the reconfigurable unit Module. 
*
*/
//The Pe_unit structure looks like this:
//////////////////////////////////////// 
//._______________________________.
//|  Pe_unit                      |     
//|    .__________.               |
//|    |          |           clk |<----
//|    | Fu pe_fu |    cfg_enable |<----
//|    .__________.  cfg_data<32> |<----
//|      |  /|\/|\                |
//| .___\|/__|__|___________.     |
//| |                       |     |
//| | Switchbox pe_swichbox |     |
//| ._______________________.     |
//|  /|\/|\/|\/|\ |  |  |  |      |
//.___|__|__|__|__|__|__|__|______.
//    |  |  |  | \|/\|/\|/\|/
///////////////////////////////////////

#ifndef ME_PE_UNIT_H
#define ME_PE_UNIT_H

#include "frame_app.h"
#include "pe_macrodef.h"
#include "pe_funcfg.h"
#include "pe_fu.h"
#include "pe_rootcfg.h"
#include "pe_switchbox.h"
#include "Bus_non_blocking_if.h"
#include "Bus_slave_if.h"
#include "pe_cfgmem.h"
#include "pe_controller.h"

class Pe_unit : public sc_module
{
public:
	sc_in_clk clk;
	sc_out<bool> cfg_finish;
	sc_in<bool> input_finish;                    //signal from pe_controller 
	sc_in<bool> cfg_enable;			    //signal from pe_controller 
	sc_in<sc_int<32> > in[FROM_NEIGHBOR_NUM];
	sc_out<sc_int<32> > out[TO_NEIGHBOR_NUM];
	sc_port<Bus_non_blocking_if> bus_master_port;		//port for read/write on bus
	Fu pe_fu;
	Switchbox pe_swichbox;
	PE_cfg_mem *pe_cfgmem;

	SC_HAS_PROCESS(Pe_unit);
	Pe_unit(sc_module_name name_unit
		,Uint32 _unique_priority) 
		: sc_module(name_unit)
		,unique_priority(_unique_priority)
	{	
		pe_cfgmem = new PE_cfg_mem("PE_CFGMEM",0xefffff00,0xefffff33,0);
		SC_THREAD(main);
		sensitive << clk.pos(); 
		SC_THREAD(config);
		sensitive << cfg_enable<<clk;
	}
	void config();
	void in_switchbox();
	void out_switchbox();
	void in_fu();
	void out_fu();
	void do_compute();
	void fetchdata(Uint32 address, Uint32 * data);
	void main();
       ~Pe_unit();
private:
	Uint32 unique_priority;
	Uint32 inst;			
		
};

#endif