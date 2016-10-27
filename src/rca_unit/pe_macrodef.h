/*
*  pe_macrodef.h
*
*  The macro defination
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-11-18 16:38:26 Created.
*
*  Description: This file mainly defines the macros used in the pe_* files. 
*
*/

#ifndef ME_PE_MACRODEF_H
#define ME_PE_MACRODEF_H

#define FROM_FU_NUM 1
#define TO_FU_NUM 2
#define FROM_NEIGHBOR_NUM 4
#define TO_NEIGHBOR_NUM 4

#define NEIGHBOR_NUM 4
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

#define FUN_TYPE_MUM 2

/************************************************************************/
/* The configuration definition                                         */
/* rout part:                                                           */
/*                      31|30|29|28|27|26|25|24|23 22 21 20|19|18|17|16 */
/*     in a:             N| E| S| W|                                    */
/*     in b:                         N| E| S| W|                        */
/*      out:                                               | N| E| S| W */
/*                                                                      */
/* function part:                                                       */
/*                      15 14 13 12 11 10  9  8  7  6  5  4| 3  2  1  0 */
/*                                                         | 0 : add    */
/*                                                         | 1 : sub    */
/*                                                         | 2 : ...    */
/************************************************************************/
#define IS_IN_A_NORTH(CFWORD)		((CFWORD & 0x80000000) >> 31)
#define IS_IN_A_EAST(CFWORD)		((CFWORD & 0x40000000) >> 30)
#define IS_IN_A_SOUTH(CFWORD)		((CFWORD & 0x20000000) >> 29)
#define IS_IN_A_WEST(CFWORD)		((CFWORD & 0x10000000) >> 28)

#define IS_IN_B_NORTH(CFWORD)		((CFWORD & 0x08000000) >> 27)
#define IS_IN_B_EAST(CFWORD)		((CFWORD & 0x04000000) >> 26)
#define IS_IN_B_SOUTH(CFWORD)		((CFWORD & 0x02000000) >> 25)
#define IS_IN_B_WEST(CFWORD)		((CFWORD & 0x01000000) >> 24)

#define IS_OUT_NORTH(CFWORD)		((CFWORD & 0x00080000) >> 19)
#define IS_OUT_EAST(CFWORD)			((CFWORD & 0x00040000) >> 18)
#define IS_OUT_SOUTH(CFWORD)		((CFWORD & 0x00020000) >> 17)
#define IS_OUT_WEST(CFWORD)			((CFWORD & 0x00010000) >> 16)

#define FU_MASK						0X0000000F
#define FU_TYPE(CFWORD)				(CFWORD & FU_MASK)

#endif