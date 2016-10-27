/*
*  config.lex
*
*  lex parse
*
*  Copyright (C) 2009  Wang Huan
*
*  2009-12-3 20:50:53 Created.
*
*  Description: This file mainly define the Syntax Rules. 
*
*/
%{

#include <stdlib.h>


#include "config.tab.h"

char*    errpos;

int line_num = 0;

%}

DIGIT    [0-9]
HEXDIGIT [0-9a-fA-F]

%%

CORE             {       return TK_CORE;             }
MAIN             {       return TK_MAIN;             }
WRITE            {       return TK_WRITE;            }
BUFFER           {       return TK_BUFFER;           }
MIPS             {       return TK_MIPS;             }
ARM              {       return TK_ARM;              } 
BUS_MASTER		 {       return TK_BUS_MASTER;       }
SLOW_MEM		 {       return TK_SLOW_MEM;		 }
BUS              {       return TK_BUS;              }
AHB              {       return TK_AHB;              }
MEM_CTRL		 {		 return TK_MEMCTRL;  		 }
ZeroWaitMemCtrl  {		 return TK_ZEROWAITMEMCTRL;  }
WaitMemCtrl  	 {		 return TK_WAITMEMCTRL;  	 }
RowBufferMemCtrl {		 return TK_ROWBUFFERMEMCTRL; }
MEMORY_SUBSYSTEM {       return TK_MEM_SUBSYSTEM;    }
IPREFETCH_BUFFER {       return TK_IPREFETCH_BUFFER; }
IMICROTLB        {       return TK_IMICROTLB;        } 
DMICROTLB        {       return TK_DMICROTLB;        } 
TLB              {       return TK_TLB;              } 
MMU              {       return TK_MMU;              } 
ICACHE           {       return TK_ICACHE;           } 
DCACHE           {       return TK_DCACHE;           } 
ITCM	         {       return TK_ITCM;             }
DTCM	         {       return TK_DTCM;             }
IPB				 {		 return TK_IPB;				 }
MEMORY           {       return TK_MEMORY;           } 
FUNCMEM          {       return TK_FUNCMEM;          } 
RR               {       return TK_RR;               } 
DEFAULT          {       return TK_DEFAULT;          } 
TRACE            {       return TK_TRACE;            } 

SDRAM          	 {       yylval.ival = 2; return TK_SDRAM;       } 
SRAM           	 {       yylval.ival = 1; return TK_SRAM;         } 
RAWMEMORY		 {		 yylval.ival = 0; return TK_RAWMEMORY;		 }

MPMCGX175		 {		 return TK_MPMCGX175;		 }
TMRSP804		 {		return TK_TMRSP804; 		}
UARTPL011		 {		return TK_UARTPL011; 		}
VICPL190		 {		return TK_VICPL190;  		}
SSMCPL093		 {		return TK_SSMCPL093;		}
SYSSP810		 {		return TK_SYSSP810;			}
CLCDCPL110		 {		return TK_CLCDCPL110;		}
DMACPL080		 {		return TK_DMACPL080;		}
AACIPL041		 {		return TK_AACIPL041; 		}


[Oo][Nn]         {       
                         yylval.ival = 1;

                         return TK_ON;               
                 } 

[Oo][Ff][Ff]     {
                         yylval.ival = 0;

                         return TK_ON ;              
                 } 

{DIGIT}+         |
0x{HEXDIGIT}+    |
0X{HEXDIGIT}+    {        
                      yylval.uival = strtoul( yytext, &errpos, 0 );
 
                      return TK_NUMBER;
                 }

[a-zA-Z0-9\/\.-]+ {       
                         yylval.char_ptr = strdup(yytext);

                         return TK_NAME;
                 }       

[ \t]+           ;
"\n"             { line_num++; }

"}"              {       return yytext[0];            }
"{"              {       return yytext[0];            }
":"              {       return yytext[0];            }
","              {       return yytext[0];            }

#[^\n]*\n     ;
.             { printf("syntax error at [%c] at line %d\n", *yytext, line_num ); };

%%

int yyerror( char* s )
{
	printf("%d %s\n", line_num, s );

	return 0;
}

