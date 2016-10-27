/*
*  bus.h
*
*  Bus module definition
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-30 15:44:14 Created.
*
*  Description: The Simple bus is modified from SystemC's example. 
*
*  bus.h : The bus.
*
*	 The bus is derived from the following interfaces, and
*         contains the implementation of these: 
*    - blocking : burst_read/burst_write
*    - non-blocking : read/write/get_status
*    - direct : direct_read/direct_write
*  Original Author: Ric Hilderink, Synopsys, Inc., 2001-10-11
*  Modified by Wang Huan, SEU, 2009-11-30
*/
//The Bus structure looks like this:
/////////////////////////////// 
//.______________________.
//|  Bus                 |     
//|                  clk |<----
//|       Bus_arbiter_if |---->
//|         Bus_slave_if |---->
//.______________________.
///////////////////////////////
#ifndef ME_BUS_H
#define ME_BUS_H

#include "bus_types.h"
#include "bus_request.h"
#include "bus_direct_if.h"
#include "bus_non_blocking_if.h"
#include "bus_blocking_if.h"
#include "bus_arbiter_if.h"
#include "bus_slave_if.h"

#define TRACE_BUS_INFO 1
#undef TRACE_BUS_INFO

#undef TRACE_INFO
#ifdef TRACE_BUS_INFO
#define TRACE_INFO if(1)
#else
#define TRACE_INFO if(0)
#endif

class Bus
: public Bus_direct_if
, public Bus_non_blocking_if
, public Bus_blocking_if
, public sc_module
{
public:
	// ports
	sc_in_clk clock;
	sc_port<Bus_arbiter_if> arbiter_port;
	sc_port<Bus_slave_if, 0> slave_port;
	
	SC_HAS_PROCESS(Bus);
	
	// constructor
	Bus(sc_module_name name_
		, bool verbose = false)
		: sc_module(name_)
		, m_verbose(verbose)
		, m_current_request(0)
	{
		// process declaration
		SC_METHOD(main_action);
		dont_initialize();
		sensitive << clock.neg();
	}
	
	// process
	void main_action();
	
	// direct BUS interface
	bool direct_read(int *data, Uint32 address);
	bool direct_write(int *data, Uint32 address);
	
	// non-blocking BUS interface
	void Read(Uint32 unique_priority
		, Uint32 *data
		, Uint32 address
		, bool lock = false);
	void Write(Uint32 unique_priority
		, Uint32 *data
		, Uint32 address
		, bool lock = false);
	bus_status get_status(unsigned int unique_priority);
	
	// blocking BUS interface
	bus_status burst_read(Uint32 unique_priority
		, Uint32 *data
		, unsigned int start_address
		, unsigned int length = 1
		, bool lock = false);
	bus_status burst_write(unsigned int unique_priority
		, Uint32 *data
		, unsigned int start_address
		, unsigned int length = 1
		, bool lock = false);
	
private:
	void handle_request();
	void end_of_elaboration();
	Bus_slave_if * get_slave(unsigned int address);
	Bus_request * get_request(unsigned int priority);
	Bus_request * get_next_request();
	void clear_locks();
	
private:
	bool m_verbose;
	bus_request_vec m_requests;
	Bus_request *m_current_request;
public:
	//signals for trace
	sc_uint<2>	HTRANS;
	sc_uint<32> HADDR;
	sc_uint<1>	HWRITE; /*1:write, 0:read*/
	sc_uint<1>	HREADY;
	sc_uint<32>	HRDATA;
	sc_uint<32>	HWDATA;
	sc_uint<3>	HSIZE;
	
}; // end class simple_bus

#endif
