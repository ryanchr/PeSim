/*
*  bus_direct_if.h
*
*  The direct BUS/Slave interface definition
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-30 15:59:55 Created.
*
*  Description: The Simple bus is modified from SystemC's example. 
*  Original Author: Ric Hilderink, Synopsys, Inc., 2001-10-11
*  Modified by Wang Huan, SEU, 2009-11-30
*/
#ifndef ME_BUS_DIRECT_IF_H
#define ME_BUS_DIRECT_IF_H

#include <systemc.h>

class Bus_direct_if
: public virtual sc_interface
{
public:
	// direct BUS/Slave interface
	virtual bool direct_read(int *data, unsigned int address) = 0;
	virtual bool direct_write(int *data, unsigned int address) = 0;
	
}; // end class simple_bus_direct_if

#endif
