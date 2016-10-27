/*
*  pe_fu.cpp
*
*  Functional part of PE implementation
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-18 10:39:15 Created.
*
*  2009-11-18 15:31:01 Change the switch-case to register-callback. 
*
*  Description: This file mainly implements the functional part of the reconfigurable unit. 
*
*/
#include "frame_app.h"
#include "pe_fu.h"

Fu::Fu()
{
	//The func is initialized to func_add.
	func = NULL;
	register_func(func_add);
}

void Fu::config(sc_uint<32> arg_cfword)
{
	//The func is registered according to the configuration.
	fcfg.funtype = (FUNTYPE)FU_TYPE(arg_cfword);
	switch(fcfg.funtype)
	{
	case add:
		register_func(func_add);
		break;
	case sub:
		register_func(func_sub);
		break;
	default:
		break;
	}
}

void Fu::compute(Fu *p)
{
	//It will call the function registered by the register_func()
	if (func == NULL)	//It is very dangerous to call a function which points to nothing!
	{
		cout << "Please register the Fu::func" << endl;
		exit(1);
	}
	func(p);

#ifdef ENABLE_DEBUG
	cout << "********************************************************" << endl;
	cout << "void Fu::compute()    at time " << sc_time_stamp() << endl;
	cout << "funtype = " << fcfg.funtype << endl;
#endif
	switch(fcfg.funtype)
	{
	case add:
		to_switchbox[0] = from_switchbox[0] + from_switchbox[1];
		break;
	case sub:
		to_switchbox[0] = from_switchbox[0] - from_switchbox[1];
		break;
	default:
		break;
	}
#ifdef ENABLE_DEBUG
	cout << "to_switchbox[0] = " << to_switchbox[0] << endl;
#endif
}


void Fu::register_func(callback_t f)
{
	//Register func.
	func = f;
}



void Fu::func_add(void *p)
{
	Fu *a = (Fu *)p;
	a->to_switchbox[0] = a->from_switchbox[0] + a->from_switchbox[1];
}

void Fu::func_sub(void *p)
{
	Fu *a = (Fu *)p;
	a->to_switchbox[0] = a->from_switchbox[0] - a->from_switchbox[1];
}