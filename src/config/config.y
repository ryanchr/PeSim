/*
*  config.y
*
*  yacc parse
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-12-3 20:51:00 Created.
*
*  Description: This file mainly define the Syntax Rules. 
*
*/
%{

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
#include <dlfcn.h>
#include <stdarg.h>
using namespace std;

#include "initializer.h"

#define PERIPHERAL_PARAM_LIST_MAX	50

int periph_param_list[ PERIPHERAL_PARAM_LIST_MAX ];
int periph_param_count = 0;

int  yylex( void );
void yyerror ( char const * );

extern FILE*        yyin;

extern Initializer *init;

#define DEBUG 1
%}

%union {
        unsigned int        uival;
        int                 ival;
        char*               char_ptr;     
}

%token TK_BUS_MASTER
%token TK_SLOW_MEM
%token TK_CORE
%token TK_MAIN
%token TK_WRITE
%token TK_BUFFER
%token TK_MIPS TK_ARM
%token TK_NAME
%token TK_BUS
%token TK_AHB
%token TK_MEMCTRL
%token TK_ZEROWAITMEMCTRL
%token TK_WAITMEMCTRL
%token TK_ROWBUFFERMEMCTRL
%token TK_MPMCGX175
%token TK_MEM_SUBSYSTEM
%token TK_IPREFETCH_BUFFER
%token TK_MMU
%token TK_IMICROTLB
%token TK_DMICROTLB
%token TK_TLB
%token TK_ICACHE
%token TK_DCACHE
%token TK_ITCM
%token TK_DTCM
%token TK_IPB
%token TK_MEMORY
%token TK_FUNCMEM
%token TK_SDRAM
%token TK_SRAM
%token TK_RR
%token TK_TRACE
%token TK_NUMBER 
%token TK_ON
%token TK_DEFAULT
%token TK_RAWMEMORY
%token TK_VICPL190
%token TK_UARTPL011
%token TK_TMRSP804
%token TK_SSMCPL093
%token TK_SYSSP810
%token TK_CLCDCPL110
%token TK_DMACPL080
%token TK_AACIPL041

%type  <char_ptr> TK_NAME
%type  <uival>    TK_NUMBER 
%type  <ival>     TK_ON
%type  <ival>     TK_SDRAM

%%

////////////////////////////////////////////////////////////////////
//////         $1     $2          $3       $4           $5
config : core_spec bus_master slow_mem bus_spec mem_subsystem_spec 
{
#ifdef DEBUG
	cerr << "yyparse >> config : core_spec bus_spec slow_mem mem_subsystem_spec succeed!" 
		<< endl;
#endif
} 
;

////////////////////////////////////////////////////////////////////
//////         $1           $3           $5   
core_spec : TK_CORE ':' TK_ARM  ',' TK_NUMBER  
{
#ifdef DEBUG
	cerr << "yyparse >> core_spec : ARM ... " << "frequency:" << $5 << "MHz" <<endl;
#endif
}
          | TK_CORE ':' TK_MIPS ',' TK_NUMBER 
{
#ifdef DEBUG
	cerr << "yyparse >> core_spec : MIPS ... " << "frequency:" << $5 << "MHz" <<endl;
#endif
}
;

/////////////////////////////////////////////////////////////////////////////////////
//////                      unique_priority  start_address    lock        timeout
//////             $1              $3            $5            $7           $9
bus_master : TK_BUS_MASTER ':' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER
{
#ifdef DEBUG
	cerr << "yyparse >> bus_master_spec : " << "unique_priority: " << $3 << endl 
		 << "                             start_address: " << $5 << endl
		 << "                             lock: " << $7 << endl
		 << "                             timeout: " << $9 << endl;
#endif
	init->set_bus_master($3, $5, $7, $9);
} 
;

/////////////////////////////////////////////////////////////////////////////////////
//////                    start_address end_address    wait_states
//////             $1          $3            $5            $7      
slow_mem : TK_SLOW_MEM ':' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER
{
#ifdef DEBUG
	cerr << "yyparse >> bus_slow_mem : " << "start_address: " << $3 << endl 
		 << "                          end_address: " << $5 << endl
		 << "                          wait_states: " << $7 << endl;
#endif
	init->set_memory($3, $5, $7);
} 
;

////////////////////////////////////////////////////////////////////
//////         $1       $3           $5  
bus_spec : TK_BUS ':' TK_AHB ',' TK_NUMBER
{
#ifdef DEBUG
	cerr << "yyparse >> bus_spec : BUS ... " << endl;
#endif
}
;


////////////////////////////////////////////////////////////////////
//////                     $1                 $3     $4          $5         $6       $7        $8           $9        $10
mem_subsystem_spec : TK_MEM_SUBSYSTEM '{' mwb_spec 
										iutlb_spec 
										dutlb_spec 
										tlb_spec 
										mmu_spec 
										icache_spec 
										dcache_spec 
										itcm_spec 
										dtcm_spec 
										ipb_spec 
										mem_spec '}'
{
#ifdef DEBUG
	cerr << "yyparse >> mem_subsystem_spec : MEM_SUBSYSTEM { ... }" 
		<< endl;
#endif
}
;

////////////////////////////////////////////////////////////////////
//////       $1                 $3          $5          $7     
mwb_spec : TK_MAIN TK_WRITE TK_BUFFER ':'  TK_ON ',' TK_NUMBER 
{
#ifdef DEBUG
	cerr << "yyparse >> mwb_spec : MAIN WRITE BUFFER ..." << endl;
#endif
}
;

////////////////////////////////////////////////////////////////////
//////       $1                  $3         $5            $7            $9       
iutlb_spec : TK_IMICROTLB ':'  TK_ON ',' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER 
{
#ifdef DEBUG
	cerr << "yyparse >> iutlb_spec : TLB ..." 
		<< $3 << ", " << $5 << ", " << $7 << ", " << $9 << endl;
#endif
	        
}
;

////////////////////////////////////////////////////////////////////
//////       $1                  $3         $5            $7            $9       
dutlb_spec : TK_DMICROTLB ':'  TK_ON ',' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER 
{
#ifdef DEBUG
	cerr << "yyparse >> dutlb_spec : TLB ..." 
		<< $3 << ", " << $5 << ", " << $7 << ", " << $9 << endl;
#endif

}
;

////////////////////////////////////////////////////////////////////
//////       $1          $3         $5            $7            $9             $11    
tlb_spec : TK_TLB ':'  TK_ON ',' TK_NUMBER ',' TK_NUMBER ',' 
								 TK_NUMBER  ',' TK_NUMBER 
{
#ifdef DEBUG
	cerr << "yyparse >> tlb_spec : TLB ..." 
		<< $3 << ", " << $5 << ", " << $7 << ", " << $9 << ", " << $11 << endl;
#endif

}
;

////////////////////////////////////////////////////////////////////
//////       $1          $3          $5            
mmu_spec : TK_MMU ':'  TK_ON ',' TK_NUMBER
{
#ifdef DEBUG
	cerr << "yyparse >> mmu_spec : MMU ..." << endl;
#endif

}
;

////////////////////////////////////////////////////////////////////
//////           $1          $3          $5             $7             $9    
icache_spec : TK_ICACHE ':'  TK_ON ',' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER
{
#ifdef DEBUG
	cerr << "yyparse >> icache_spec : ICACHE ..." << endl;
#endif

}
;

////////////////////////////////////////////////////////////////////
//////           $1          $3          $5             $7
dcache_spec : TK_DCACHE ':'  TK_ON ',' TK_NUMBER ',' TK_NUMBER ',' 
///					$9           $11         $13         $15   
				TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER ',' TK_ON ',' 
				TK_NUMBER
{
#ifdef DEBUG
	cerr << "yyparse >> dcache_spec : DCACHE ..." << endl;
#endif

}
;

////////////////////////////////////////////////////////////////////
//////        $1          $3          $5             $7 
itcm_spec : TK_ITCM ':' TK_ON ',' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER
{
#ifdef DEBUG
	cerr << "yyparse >> itcm_spec : ITCM ..." << endl;
#endif

}
;

////////////////////////////////////////////////////////////////////
//////        $1          $3          $5             $7 
dtcm_spec: TK_DTCM ':' TK_ON ',' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER
{
#ifdef DEBUG
	cerr << "yyparse >> dtcm_spec : DTCM ..." << endl;
#endif
}
;

////////////////////////////////////////////////////////////////////
//////      $1        $3          $5   
ipb_spec: TK_IPB ':' TK_ON ',' TK_NUMBER
{
#ifdef DEBUG
	cerr << "yyparse >> ipb_spec : ..." << endl;
#endif

}
;

////////////////////////////////////////////////////////////////////
mem_spec : TK_MEMORY '{' mem_region_spec_list '}'
{ 
#ifdef DEBUG
	cerr << "yyparse >> mem_spec : MEMORY : mem_region_spec_list " << endl;
#endif

}
;

////////////////////////////////////////////////////////////////////
mem_region_spec_list : mem_region_spec 
{ 
#ifdef DEBUG
	cerr << "yyparse >> mem_region_spec_list : mem_region_spec" << endl;
#endif

}
////////////////////////////////////////////////////////////////////
//////                         $1                 $2
| mem_region_spec_list mem_region_spec
{ 
#ifdef DEBUG
	cerr << "yyparse >> mem_region_spec_list : " 
		<< "mem_region_spec_list mem_region_spec" << endl;
#endif

} 
;


////////////////////////////////////////////////////////////////////
//////               $1     $2               $4           $6
mem_region_spec : TK_NAME ':' TK_RAWMEMORY 
				'{' TK_NAME ',' TK_NUMBER ',' TK_NUMBER '}'
{ 
#ifdef DEBUG
	cerr << "yyparse >> mem_region_spec : RAWMEMORY ..." << endl;
#endif

}
| TK_NAME ':' TK_VICPL190 
	'{' TK_NAME ',' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER '}'
{
#ifdef DEBUG
	cerr << "yyparse >> mem_region_spec : VICPL190..." << endl;
#endif

}
| TK_NAME ':' TK_TMRSP804 
	'{' TK_NAME ',' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER '}'
{
#ifdef DEBUG
	cerr << "yyparse >> mem_region_spec : TMRSP804..." << endl;
#endif

}
| TK_NAME ':' TK_CLCDCPL110 '{' TK_NAME ',' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER '}'
{
#ifdef DEBUG
	cerr << "yyparse >> mem_region_spec : CLCDCPL110..." << endl;
#endif

}
| TK_NAME ':' TK_UARTPL011 
	'{' TK_NAME ',' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER '}'
{
#ifdef DEBUG
	cerr << "yyparse >> mem_region_spec : UARTPL011..." << endl;
#endif

}
| TK_NAME ':' TK_MPMCGX175 
	'{' TK_NAME ',' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER ','
					TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER ','
					TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER ','
					TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER '}'
{
#ifdef DEBUG
	cerr << "yyparse >> mem_region_spec : MPMCGX175..." << endl;
#endif

}
| TK_NAME ':' TK_SSMCPL093 
	'{' TK_NAME ',' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER '}'
{
#ifdef DEBUG
	cerr << "yyparse >> mem_region_spec : SSMCPL093..." << endl;
#endif

}
| TK_NAME ':' TK_SYSSP810 '{' TK_NAME ',' TK_NUMBER ',' TK_NUMBER ',' 
							TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER '}'
{
#ifdef DEBUG
	cerr << "yyparse >> mem_region_spec : SYSSP810..." << endl;
#endif
	
}
| TK_NAME ':' TK_DMACPL080 
	'{' TK_NAME ',' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER '}'
{
#ifdef DEBUG
	cerr << "yyparse >> mem_region_spec : DMACPL080..." << endl;
#endif

}
| TK_NAME ':' TK_AACIPL041 
	'{' TK_NAME ',' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER ',' TK_NUMBER '}'
{
#ifdef DEBUG
	cerr << "yyparse >> mem_region_spec : AACIPL041..." << endl;
#endif

}
;

%%

void yyerror( char const *s )
{
	fprintf(stderr,"%s\n",s);
}

void config_parse( string name )
{
	yyin = fopen( name.c_str(), "r" ); 

	yyparse();
}


