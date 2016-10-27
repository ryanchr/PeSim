/*
*  initializer.h
*
*  initializer definition
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-12-4 15:35:11 Created.
*
*  Description: The initializer init the module through the cfgfile. 
*/
#ifndef ME_INITIALIZER_H
#define ME_INITIALIZER_H

#include "frame_app.h"
/*include the module header you want to initialize by the cfgfile*/
#include "bus.h"
#include "memory.h"
#include "bus_master.h"

class ParaMemory
{
public:
	Uint32 start_address;
	Uint32 end_address;
	Uint32 nr_wait_states;

	ParaMemory()
	{
		start_address = 0;
		end_address = 0;
		nr_wait_states = 0;
	}
};

class ParaBusMaster
{
public:
	Uint32 unique_priority;
	Uint32 start_address;
	Uint32 lock;
	Uint32 timeout;

	ParaBusMaster()
	{
		unique_priority = 0;
		start_address = 0;
		lock = 0;
		timeout = 0;
	}
};

class Initializer
{
public:
	/*memory*/
	ParaMemory _memory;
	/*bus_master*/
	ParaBusMaster _bus_master;
public:
	Initializer();
	
	void set_memory(Uint32 start_address
		, Uint32 end_address
		, Uint32 nr_wait_states);
	
	void set_bus_master(Uint32 unique_priority
		, Uint32 start_address
		, Uint32 lock
		, Uint32 timeout);
};

#endif
