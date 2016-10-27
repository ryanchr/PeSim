/*
*  pe_rootcfg.h
*
*  Root part of PE configuration
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-19 10:44:52 Created.
*
*  Description: This file mainly defines the root part of the PE configuration. 
*
*/
#ifndef ME_PE_ROOTCFG_H
#define ME_PE_ROOTCFG_H

#include "pe_macrodef.h"

class Rootcfg
{
public:
	bool from[TO_FU_NUM][FROM_NEIGHBOR_NUM];
	bool to[FROM_FU_NUM][TO_NEIGHBOR_NUM];
};

#endif