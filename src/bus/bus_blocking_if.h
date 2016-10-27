/*
*  bus_blocking_if.h
*
*  Blocking bus interface definition
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-30 15:58:36 Created.
*
*  Description: The Simple bus is modified from SystemC's example. 
*  Original Author: Ric Hilderink, Synopsys, Inc., 2001-10-11
*  Modified by Wang Huan, SEU, 2009-11-30
*/
#ifndef ME_BUS_BLOCKING_IF_H
#define ME_BUS_BLOCKING_IF_H

#include "bus_types.h"

class Bus_blocking_if
: public virtual sc_interface
{
public:
	// blocking BUS interface
	virtual bus_status burst_read(unsigned int unique_priority
		, Uint32 *data
		, unsigned int start_address
		, unsigned int length = 1
		, bool lock = false) = 0;
	virtual bus_status burst_write(unsigned int unique_priority
		, Uint32 *data
		, unsigned int start_address
		, unsigned int length = 1
		, bool lock = false) = 0;
	
}; // end class simple_bus_blocking_if

#endif
