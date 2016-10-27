/*
*  Pe_switchbox.h
*
*  Local root part of PE interfaces
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-19 10:57:53 Created.
*
*  Description: This file mainly defines the local root part of the reconfigurable unit. 
*
*/
#ifndef ME_PE_SWITCHB0X_H
#define ME_PE_SWITCHB0X_H

#include "pe_macrodef.h"
#include "pe_rootcfg.h"

class Switchbox
{
public:
	sc_int<32> from_fu[FROM_FU_NUM];
	sc_int<32> to_fu[TO_FU_NUM];
	sc_int<32> from_neighbor[FROM_NEIGHBOR_NUM];
	sc_int<32>  to_neighbor[TO_NEIGHBOR_NUM];
	Rootcfg rcfg;

	void config(sc_uint<32> arg_cfword);
	void sw_neighbor_in();
	void sw_neighbor_out();
};

#endif