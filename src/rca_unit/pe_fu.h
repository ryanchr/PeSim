/*
*  pe_fu.h
*
*  Functional part of PE interfaces
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-18 10:36:02 Created.
*
*  2009-11-18 15:31:01 Change the switch-case to register-callback. 
*
*  Description: This file mainly defines the functional part of the reconfigurable unit. 
*  The main idea is register and callback!
*/
#ifndef ME_PE_FUN_H
#define ME_PE_FUN_H

#include "pe_macrodef.h"
#include "pe_funcfg.h"

typedef void (* callback_t)(void *);

class Fu
{
public:
	sc_int<32> from_switchbox[TO_FU_NUM];
	sc_int<32> to_switchbox[FROM_FU_NUM];
	Funcfg fcfg;
	
	Fu();
	void config(sc_uint<32> arg_cfword);
	void compute(Fu *);
	void register_func(callback_t f);

private:
	callback_t func;
	static void func_add(void *);
	static void func_sub(void *);
};

#endif