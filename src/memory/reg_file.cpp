/*
*  reg_file.cpp
*
*  Register file Class implementation
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-30 14:21:24 Created.
*
*  Description: This file mainly implements the Register file.
*
*/
#include "reg_file.h"

RegFile::RegFile()
{
	reg_num = 0;
	regs = NULL;
}

RegFile::~RegFile()
{
	if (regs != NULL)
	{
		delete regs;
		regs = NULL;
	}
}

int RegFile::get_reg_num()
{
	return reg_num; 
}

void RegFile::print_reg_value()
{
	for (int i = 0; i < reg_num != 0; i++)
	{
		printf("reg[%d] = %s", i, regs[i]);
	}
}