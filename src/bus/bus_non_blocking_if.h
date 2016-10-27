/*
*  bus_non_blocking_if.h
*
*  Non-blocking bus interface definition
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-30 16:00:53 Created.
*
*  Description: The Simple bus is modified from SystemC's example. 
*  Original Author: Ric Hilderink, Synopsys, Inc., 2001-10-11
*  Modified by Wang Huan, SEU, 2009-11-30
*/
#ifndef ME_BUS_NON_BLOCKING_IF_H
#define ME_BUS_NON_BLOCKING_IF_H

#include "bus_types.h"

class Bus_non_blocking_if
: public virtual sc_interface
{
public:
	// non-blocking BUS interface
	virtual void Read(Uint32 unique_priority
		, Uint32 *data
		, Uint32 address
		, bool lock = false) = 0;
	virtual void Write(Uint32 unique_priority
		, Uint32 *data
		, Uint32 address
		, bool lock = false) = 0;
	
	virtual bus_status get_status(unsigned int unique_priority) = 0;
	
}; // end class simple_bus_non_blocking_if

#endif
