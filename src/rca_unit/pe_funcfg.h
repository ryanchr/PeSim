/*
*  pe_funcfg.h
*
*  Functional part of PE configuration
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-18 16:38:26 Created.
*
*  Description: This file mainly defines the functional part of the PE configuration. 
*
*/
#ifndef PE_FUNCFG_H
#define PE_FUNCFG_H

#include "pe_macrodef.h"

enum FUNTYPE
{
	add = 0,
	sub = 1
};

class Funcfg
{
public:
	FUNTYPE funtype;
	
	Funcfg()
	{
		//The function type is initialized to add.
		funtype = add;
	}
};

#endif