/*
*  initializer.h
*
*  initializer definition
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-12-4 16:01:34 Created.
*
*  Description: The initializer init the module through the cfgfile. 
*/
#include "initializer.h"

Initializer::Initializer()
{
	/*add what you want here*/
}

void Initializer::set_bus_master(Uint32 unique_priority
	, Uint32 start_address
	, Uint32 lock
	, Uint32 timeout)
{
	_bus_master.unique_priority = unique_priority;
	_bus_master.start_address = start_address;
	_bus_master.lock = lock;
	_bus_master.timeout = timeout;
}

void Initializer::set_memory(Uint32 start_address
	, Uint32 end_address
	, Uint32 nr_wait_states)
{
	_memory.start_address = start_address;
	_memory.end_address = end_address;
	_memory.nr_wait_states = nr_wait_states;
}