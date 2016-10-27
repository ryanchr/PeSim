/*
*  bus_arbiter_if.h
*
*  Bus arbiter interface definition
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-30 15:55:41 Created.
*
*  Description: The Simple bus is modified from SystemC's example. 
*  Original Author: Ric Hilderink, Synopsys, Inc., 2001-10-11
*  Modified by Wang Huan, SEU, 2009-11-30
*/
#ifndef ME_BUS_ARBITER_IF_H
#define ME_BUS_ARBITER_IF_H

#include "bus_types.h"


class Bus_arbiter_if
: public virtual sc_interface
{
public:
	virtual Bus_request * 
		arbitrate(const bus_request_vec &requests) = 0;
	
}; // end class simple_bus_arbiter_if

#endif
