/*
* pe_cfgmem.h
*
*  Memory Module
*
*  Copyright (C) 2010  Ren Chen
*
*  2010-03-27 16:04:24 Created.
*
*  Description: This file mainly defines the PE config memory Module. 
*
*/

#ifndef PE_CFGMEMORY_H
#define PE_CFGMEMORY_H

#include "frame_app.h"
#include "bus_types.h"
#include "bus_slave_if.h"

#define CFG_ENABLE 0xefffff04
#define CFG_DATA 0xefffff14
#define IMPORT_DATA 0xefffff18
#define OUTPUT_DATA 0xefffff28

enum CFGMemCmd {
	CFGCmdRead,			/* read memory from target (simulated prog) to host */
	CFGCmdWrite			/* write memory from host (simulator) to target */
};


typedef enum cfgmem_fault_type {
	cfgmem_fault_none = 0,		/* no fault */
	cfgmem_fault_access,		/* storage access fault */
	cfgmem_fault_alignment,		/* storage alignment fault */
	cfgmem_fault_overflow,		/* signed arithmetic overflow fault */
	cfgmem_fault_div0,		/* division by zero fault */
	cfgmem_fault_invalid,             /* invalid arithmetic operation */ 
	/* added to allow SQRT{S,T} in FIX exts */
	cfgmem_fault_break,		/* BREAK instruction fault */
	cfgmem_fault_unimpl,		/* unimplemented instruction fault */
	cfgmem_fault_internal		/* internal S/W fault */
}cfgfault_t;

class PE_cfg_mem
:public Bus_slave_if 
,public sc_module
{
public:
  // ports
  sc_in_clk clock;

  
  SC_HAS_PROCESS(PE_cfg_mem);

  // constructor
  PE_cfg_mem(sc_module_name name_
		      , unsigned int start_address
		      , unsigned int end_address
		      , unsigned int nr_wait_states)
    : sc_module(name_)
    , m_start_address(start_address)
    , m_end_address(end_address)
    , m_nr_wait_states(nr_wait_states)
    , m_wait_count(0)       //FIXME ,temprotary value for testing
	{
	// process declaration
	SC_THREAD(cfgwait_loop);
       dont_initialize();
      //sensitive<< clock.neg();

	/*create a memory*/
	cfgmem = new Uint32[end_address-start_address];
	cfgmem_init();
    sc_assert(m_start_address <= m_end_address);
    sc_assert((m_end_address-m_start_address+1)%4 == 0);
	//printf("----0x%x \n" , m_end_address-m_start_address+1);
    unsigned int size = (m_end_address-m_start_address+1)/4;
     }

	  // destructor
	 ~PE_cfg_mem ();
	  // process
	  void cfgwait_loop();
	  void cfgmem_init();
	// Slave Interface
	bus_status Read(Uint32 addr, Uint32 *value);
	bus_status Write(Uint32 addr, Uint32 *value);

 	unsigned int start_address() const;
  	unsigned int end_address() const;
      bool direct_read(Sint32 *data, unsigned int address);
      bool direct_write(Sint32 *data, unsigned int address);
	 #if 0
      cfgfault_t MemAccess(enum cfgMemCmd cmd,		/* Read (from sim mem) or Write */
		Uint32 addr,		/* target address to access */
		void *vp,			/* host memory address to access */
		int nbytes);		/* number of bytes to access */
	 #endif
  
private:
	  Uint32 *cfgmem;
	  Uint32 m_start_address , m_end_address;
	  Uint32  m_nr_wait_states;
 	  int m_wait_count;
};// end class simple_bus_slow_mem

#endif

