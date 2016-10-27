/*
*  Pe_switchbox.cpp
*
*  Local root part of PE interfaces
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-19 10:57:53 Created.
*
*  Description: This file mainly implements the local root part of the reconfigurable unit. 
*
*/
#include "frame_app.h"
#include "pe_switchbox.h"

void Switchbox::config(sc_uint<32> arg_cfword)
{
	rcfg.from[0][0] = IS_IN_A_NORTH(arg_cfword);
	rcfg.from[0][1] = IS_IN_A_EAST(arg_cfword);
	rcfg.from[0][2] = IS_IN_A_SOUTH(arg_cfword);
	rcfg.from[0][3] = IS_IN_A_WEST(arg_cfword);

	rcfg.from[1][0] = IS_IN_B_NORTH(arg_cfword);
	rcfg.from[1][1] = IS_IN_B_EAST(arg_cfword);
	rcfg.from[1][2] = IS_IN_B_SOUTH(arg_cfword);
	rcfg.from[1][3] = IS_IN_B_WEST(arg_cfword);

	rcfg.to[0][0] = IS_OUT_NORTH(arg_cfword);
	rcfg.to[0][1] = IS_OUT_EAST(arg_cfword);
	rcfg.to[0][2] = IS_OUT_SOUTH(arg_cfword);
	rcfg.to[0][3] = IS_OUT_WEST(arg_cfword);
}

void Switchbox::sw_neighbor_in()
{
#ifdef ENABLE_DEBUG
	cout << "********************************************************" << endl;
	cout << "void Switchbox::sw_neighbor_in() at time " << ss_sc_time_stamp() << endl;
#endif

	int i, j;

	for (i = 0; i < TO_FU_NUM; i++)
	{
		for (j = 0; j < FROM_NEIGHBOR_NUM; j++)
		{
#ifdef ENALBE_DEBUG
			cout << "rcfg.from[" << i << "][" << j << "] = " << rcfg.from[i][j] << endl;
#endif
			if (rcfg.from[i][j])
			{
				to_fu[i] = from_neighbor[j];
			}
		}
	}
}

void Switchbox::sw_neighbor_out()
{
#ifdef ENABLE_DEBUG
	cout << "********************************************************" << endl;
	cout << "void Switchbox::sw_neighbor_out() at time " << ss_sc_time_stamp() << endl;
#endif

	int i, j;

	for (i = 0; i < FROM_FU_NUM; i++)
	{
		for (j = 0; j < TO_NEIGHBOR_NUM; j++)
		{
#ifdef ENALBE_DEBUG
			cout << "rcfg.to[" << i << "][" << j << "] = " << rcfg.to[i][j] << endl;
#endif
			if (rcfg.to[i][j])
			{
				to_neighbor[j] = from_fu[i];
			}
		}
	}
}