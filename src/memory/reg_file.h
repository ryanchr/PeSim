/*
*  reg_file.h
*
*  Register file Class definition
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-30 14:21:24 Created.
*
*  Description: The definition of the register file of each module. 
*
*/
#ifndef ME_REG_FILE_H
#define ME_REG_FILE_H

#include "frame_app.h"

class RegFile
{
public:
	Uint32 reg_num;
	Uint32 *regs;

	RegFile();
	~RegFile();
	/***register file operation***/
	virtual int get_reg_num();
	virtual void print_reg_value();
};

#endif