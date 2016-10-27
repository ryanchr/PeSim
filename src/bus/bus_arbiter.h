/*
*  bus_arbiter.h
*
*  Bus arbitration unit definition
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-30 15:53:36 Created.
*
*  Description: The Simple bus is modified from SystemC's example. 
*  Original Author: Ric Hilderink, Synopsys, Inc., 2001-10-11
*  Modified by Wang Huan, SEU, 2009-11-30
*/
#ifndef ME_BUS_ARBITER_H
#define ME_BUS_ARBITER_H
#include <systemc.h>
#include "bus_types.h"
#include "bus_request.h"
#include "bus_arbiter_if.h"


class Bus_arbiter
: public Bus_arbiter_if
, public sc_module
{
public:
	// constructor
	Bus_arbiter(sc_module_name name_
		, bool verbose = false)
		: sc_module(name_)
		, m_verbose(verbose)
	{}
	
	Bus_request *arbitrate(const bus_request_vec &requests);
	
private:
	bool m_verbose;
	
}; // end class simple_bus_arbiter

#endif
