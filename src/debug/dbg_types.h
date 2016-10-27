/*
*  dbg_types.h
*
*  The types debugger used
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-12-7 22:31:01 Created.
*
*  Description: The definition of the types for the debugger only. 
*
*/

#ifndef ME_DBG_TYPES_H
#define ME_DBG_TYPES_H
#include "debugger.h"
enum COMMANDS
{
	//////////////////////////////////////////////////
	// CATEGORY : Execution Control
	RUN = 0,
	STEP,
	QUIT,
	READ,
		
	//////////////////////////////////////////////////
	// CATEGORY : help
	HELP,

	//////////////////////////////////////////////////
	COMMAND_MAX
};



#endif