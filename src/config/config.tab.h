/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TK_BUS_MASTER = 258,
     TK_SLOW_MEM = 259,
     TK_CORE = 260,
     TK_MAIN = 261,
     TK_WRITE = 262,
     TK_BUFFER = 263,
     TK_MIPS = 264,
     TK_ARM = 265,
     TK_NAME = 266,
     TK_BUS = 267,
     TK_AHB = 268,
     TK_MEMCTRL = 269,
     TK_ZEROWAITMEMCTRL = 270,
     TK_WAITMEMCTRL = 271,
     TK_ROWBUFFERMEMCTRL = 272,
     TK_MPMCGX175 = 273,
     TK_MEM_SUBSYSTEM = 274,
     TK_IPREFETCH_BUFFER = 275,
     TK_MMU = 276,
     TK_IMICROTLB = 277,
     TK_DMICROTLB = 278,
     TK_TLB = 279,
     TK_ICACHE = 280,
     TK_DCACHE = 281,
     TK_ITCM = 282,
     TK_DTCM = 283,
     TK_IPB = 284,
     TK_MEMORY = 285,
     TK_FUNCMEM = 286,
     TK_SDRAM = 287,
     TK_SRAM = 288,
     TK_RR = 289,
     TK_TRACE = 290,
     TK_NUMBER = 291,
     TK_ON = 292,
     TK_DEFAULT = 293,
     TK_RAWMEMORY = 294,
     TK_VICPL190 = 295,
     TK_UARTPL011 = 296,
     TK_TMRSP804 = 297,
     TK_SSMCPL093 = 298,
     TK_SYSSP810 = 299,
     TK_CLCDCPL110 = 300,
     TK_DMACPL080 = 301,
     TK_AACIPL041 = 302
   };
#endif
/* Tokens.  */
#define TK_BUS_MASTER 258
#define TK_SLOW_MEM 259
#define TK_CORE 260
#define TK_MAIN 261
#define TK_WRITE 262
#define TK_BUFFER 263
#define TK_MIPS 264
#define TK_ARM 265
#define TK_NAME 266
#define TK_BUS 267
#define TK_AHB 268
#define TK_MEMCTRL 269
#define TK_ZEROWAITMEMCTRL 270
#define TK_WAITMEMCTRL 271
#define TK_ROWBUFFERMEMCTRL 272
#define TK_MPMCGX175 273
#define TK_MEM_SUBSYSTEM 274
#define TK_IPREFETCH_BUFFER 275
#define TK_MMU 276
#define TK_IMICROTLB 277
#define TK_DMICROTLB 278
#define TK_TLB 279
#define TK_ICACHE 280
#define TK_DCACHE 281
#define TK_ITCM 282
#define TK_DTCM 283
#define TK_IPB 284
#define TK_MEMORY 285
#define TK_FUNCMEM 286
#define TK_SDRAM 287
#define TK_SRAM 288
#define TK_RR 289
#define TK_TRACE 290
#define TK_NUMBER 291
#define TK_ON 292
#define TK_DEFAULT 293
#define TK_RAWMEMORY 294
#define TK_VICPL190 295
#define TK_UARTPL011 296
#define TK_TMRSP804 297
#define TK_SSMCPL093 298
#define TK_SYSSP810 299
#define TK_CLCDCPL110 300
#define TK_DMACPL080 301
#define TK_AACIPL041 302




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 42 "config/config.y"
{
        unsigned int        uival;
        int                 ival;
        char*               char_ptr;     
}
/* Line 1489 of yacc.c.  */
#line 149 "config/config.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

