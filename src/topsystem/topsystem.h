/*
*  topsystem.h
*
*  top level module
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-12-3 20:58:53 Created.
*
*  Description: This file mainly instantiate the PE unit. 
*
*/
//The Test structure looks like this:
/////////////////////////////////////////////////////////////////  
//.______________________.     .__________________________.
//|  Driver              |     |  Pe_unit                 |   
//|                  clk |<-|->| clk                      |
//|           cfg_enable |--|->| cfg_enable               |
//|         cfg_data<32> |--|->| cfg_data<32>             |
//|                a<32> |--|->| i_east<32>    o_east<32> |---->|
//|                b<32> |--|->| i_west<32>    o_west<32> |---->|
//|                c<32> |--|->| i_north<32>  o_north<32> |---->|
//|                d<32> |--|->| i_south<32>  o_south<32> |---->|
//.______________________.  |  .__________________________.     |
//                          |                                   |
//                          |                                   |
//                          |     .______________________.      |
//                          |     |  Monitor             |      |
//                          |---->| clk      peout_e<32> |<-----|
//                          |---->| a<32>    peout_w<32> |<-----|
//                          |---->| b<32>    peout_n<32> |<-----|
//                          |---->| c<32>    peout_s<32> |<-----|
//                          |---->| d<32>                |<-----|
//                                .______________________.
/////////////////////////////////////////////////////////////////

#ifndef ME_TOPSYSTEM_H
#define ME_TOPSYSTEM_H

#include "frame_app.h"
#include "driver.h"
#include "monitor.h"
#include "pe_unit.h"
#include "bus.h"
#include "memory.h"
#include "bus_master.h"
#include "bus_arbiter.h"
#include "initializer.h"
#include "controler.h"
#include "sim-safe.h"
#include "main.h"
#include "timer.h"
#include "pe_controller.h"
#include <sys/stat.h>


class Topsys : public sc_module
{
public:
	sc_clock clock1;
	sc_signal<bool> irq;
	sc_trace_file *trfile;
	//sc_signal<bool> cfg_signal;  //config signal bewteen rca and cpu
	//sc_signal<sc_uint<32> > cfgdata_signal;
	sc_signal<sc_int<32> > in[FROM_NEIGHBOR_NUM];
	sc_signal<sc_int<32> > out[TO_NEIGHBOR_NUM];
	sc_signal<bool> cfg_finish_signal;
	sc_signal<bool> input_finish_signal;
	sc_signal<bool> cfg_enable_signal;
	Initializer *init;  
	Bus_master *master_nb;
	Bus *bus;
	Bus_arbiter *arbiter;
	Bus_slow_mem *mem_slow;
	Controler *controler;
	CoreArm *core;
	Timer *timer;
	Pe_unit *rca;	         //reconfigurable cell array
	Monitor *monitor;
	PE_Controller *pe_controller;
	
	void SimPause();
	void SimContinue();
	void MainIdle();
	

	Topsys(sc_module_name _name = sc_module_name("example")
		, Initializer *_init = NULL, int argc = 0, char* argv[] = NULL, char **envp = NULL)
		: sc_module(_name)
		, init(_init)
	{
		master_nb = new Bus_master("bmaster"
			                       , init->_bus_master.unique_priority
			                       , init->_bus_master.start_address
			                       , init->_bus_master.lock
			                       , init->_bus_master.timeout);
		bus = new Bus("bus");
		arbiter = new Bus_arbiter("arbiter");
		//mem_slow = new Bus_slow_mem("mem_slow", 0x0, 0xdfffffff, 1);
		mem_slow = new Bus_slow_mem("mem_slow"
									, init->_memory.start_address
									, init->_memory.end_address
									, init->_memory.nr_wait_states);
		controler = new Controler("controlser");
		core = new CoreArm("arm", mem_slow, 0x2);
		rca = new Pe_unit("RCA",0x1); 	//memory allocation  of pe 
		timer = new Timer("timer");
		monitor = new Monitor("monitor");
		pe_controller = new PE_Controller("pe_controller",0x0);
		
		//connect instance
		master_nb->clock(clock1);
		master_nb->bus_port(*bus);
		
		bus->clock(clock1);
		bus->arbiter_port(*arbiter);
		bus->slave_port(*mem_slow);
		bus->slave_port(*rca->pe_cfgmem);
		
		mem_slow->clock(clock1);
		
		controler->clk(clock1);
		
		core->clk(clock1);
		core->irq(irq);
		core->bus_master_port(*bus);
		/*
		rca->config_mem = new Bus_slow_mem("config_mem_slow"
									, init->_memory.start_address
									, init->_memory.end_address
									, init->_memory.nr_wait_states);*/
		//link the three models by location association
             (*pe_controller)(clock1,cfg_finish_signal,input_finish_signal,cfg_enable_signal
             			   ,in[0],in[1],in[2],in[3],*bus);
		(*rca)(clock1,cfg_finish_signal,input_finish_signal,cfg_enable_signal
			   ,in[0],in[1],in[2],in[3],out[0],out[1],out[2],out[3],*bus);	
		(*monitor)(clock1,in[0],in[1],in[2],in[3],out[0],out[1],out[2],out[3]);
		rca->pe_cfgmem->clock(clock1);
		timer->clk(clock1);
		timer->irq(irq);
		//trace vcd
		trfile = sc_create_vcd_trace_file("trace");
		CoreMain(argc, argv, envp, mem_slow);
		if (ENABLE_TRACE)
		{
			sc_trace(trfile, clock1,  "CLK");
			#ifdef TRACE_BUS_INFO
			sc_trace(trfile, master_nb->raddr,  "M_RADDR");
			sc_trace(trfile, master_nb->rdata,  "M_RDATA");
			sc_trace(trfile, master_nb->waddr,  "M_WADDR");
			sc_trace(trfile, master_nb->wdata,  "M_WDATA");	
			#endif
		}
	}
	~Topsys()
	{
		if (master_nb) {delete master_nb; master_nb = 0;}
    		if (mem_slow) {delete mem_slow; mem_slow = 0;}
    		if (bus) {delete bus; bus = 0;}
		if (arbiter) {delete arbiter; arbiter = 0;}
		if (controler) {delete controler; controler = 0;};
		if (core) {delete core; core = 0;};
		if (pe_controller) {delete pe_controller; pe_controller = 0;};
		if (rca) {delete rca; rca = 0;};
		if (timer) {delete timer; timer = 0;};
		sc_close_vcd_trace_file(trfile);
	}

private:
	bool _flag_pause;
};

#endif