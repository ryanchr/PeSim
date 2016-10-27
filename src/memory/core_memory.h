/*
*  memory.h
*
*  Memory Module
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-12-22 20:02:49 Created.
*
*  Description: This file mainly defines the Memory Module. 
*
*/
/*Address*/
/*|31|30|29|28|27|26|25|24|23|22|21|20|19|18|17|16|15|14|13|12|11|10|09|08|07|06|05|04|03|02|01|00|
 *|PTAB_TAG(5bit)|               PTAB_SET(15bits)             |11|10|09|08|07|06|05|04|03|02|01|00|
 *
 *  Level 1 Page Table     Host Memory Pages
 *                         (allocated as needed)
 *  indexed by PTAB_SET    marked by PTAB_TAG
 *  +-------------+       +----------------------+
 *  |  PTAB_SET   |------>|4k|4k|4k|4k|...(128k) |
 *  +-------------+       +----------------------+
 *  |             |
 *  +-------------+       +----------------------+
 *  |             |------>|4k|4k|4k|4k|...(128k) |
 *  +-------------+       +----------------------+
 *  |             |                 .
 *  +-------------+                 .
 *  |             |                 .
 *  +-------------+       +----------------------+
 *  |             |------>|4k|4k|4k|4k|...(128k) |
 *  +-------------+       +----------------------+
 */
#ifndef ME_MEMORY_H
#define ME_MEMORY_H

#include "frame_app.h"
#include "bus_types.h"
#include "bus_slave_if.h"

/* memory access command */
enum MemCmd {
	CmdRead,			/* read memory from target (simulated prog) to host */
	CmdWrite			/* write memory from host (simulator) to target */
};

/* number of entries in page translation hash table (must be power-of-two) */
#define MEM_PTAB_SIZE		(32*1024)
#define MEM_LOG_PTAB_SIZE	15

/* physical memory page size (must be a power-of-two) */
#define MD_PAGE_SIZE		4096
#define MD_LOG_PAGE_SIZE	12
/*
* target-dependent instruction faults
*/

typedef enum mem_fault_type {
	mem_fault_none = 0,		/* no fault */
	mem_fault_access,		        /* storage access fault */
	mem_fault_alignment,		/* storage alignment fault */
	mem_fault_overflow,		/* signed arithmetic overflow fault */
	mem_fault_div0,		        /* division by zero fault */
	mem_fault_invalid,                 /* invalid arithmetic operation */ 
	/* added to allow SQRT{S,T} in FIX exts */
	mem_fault_break,		        /* BREAK instruction fault */
	mem_fault_unimpl,		        /* unimplemented instruction fault */
	mem_fault_internal		        /* internal S/W fault */
}fault_t;

/* page table entry */
struct MemPte {
	struct MemPte *next;	/* next translation in this bucket */
	Uint32 tag;		/* virtual page number tag */
	Uint8 *page;			/* page pointer */
};

/* memory object */
struct MemObj {
	struct MemPte *ptab[MEM_PTAB_SIZE];/* inverted page table */

	/* memory object stats */
	Sint64 page_count;			/* total number of pages allocated */
	Sint64 ptab_misses;		/* total first level page tbl misses */
	Sint64 ptab_accesses;		/* total page table accesses */
};

/* compute page table set */
#define MEM_PTAB_SET(ADDR) (((ADDR) >> MD_LOG_PAGE_SIZE) & (MEM_PTAB_SIZE - 1))

/* compute page table tag */
#define MEM_PTAB_TAG(ADDR)						\
	((ADDR) >> (MD_LOG_PAGE_SIZE + MEM_LOG_PTAB_SIZE))

/* convert a pte entry at idx to a block address */
#define MEM_PTE_ADDR(PTE, IDX)						\
	(((PTE)->tag << (MD_LOG_PAGE_SIZE + MEM_LOG_PTAB_SIZE))		\
	| ((IDX) << MD_LOG_PAGE_SIZE))

/* compute address of access within a host page */
#define MEM_OFFSET(ADDR)	((ADDR) & (MD_PAGE_SIZE - 1))
class Bus_slow_mem
  : public Bus_slave_if
  , public sc_module
{
public:
  // ports
  sc_in_clk clock;

  SC_HAS_PROCESS(Bus_slow_mem);

  // constructor
  Bus_slow_mem(sc_module_name name_
		      , unsigned int start_address
		      , unsigned int end_address
		      , unsigned int nr_wait_states)
    : sc_module(name_)
    , m_start_address(start_address)
    , m_end_address(end_address)
    , m_nr_wait_states(nr_wait_states)
    , m_wait_count(-1)
	{
	// process declaration
	SC_METHOD(wait_loop);
    dont_initialize();
    sensitive << clock.pos();

	/*create a memory*/
	_mem = _MemCreate();
	/*init the memory*/
	_MemInit();
	
    sc_assert(m_start_address <= m_end_address);
    sc_assert((m_end_address-m_start_address+1)%4 == 0);
    unsigned int size = (m_end_address-m_start_address+1)/4;
  }

  // destructor
  ~Bus_slow_mem();

  // process
  void wait_loop();

  // direct Slave Interface
  bool direct_read(Sint32 *data, unsigned int address);
  bool direct_read_08(Uint8 * data, unsigned int address);
  bool direct_write(Sint32 *data, unsigned int address);
  bool direct_write_08(Uint8 *data, unsigned int address);
  bool mem_wstrcpy(Uint32 addr, char *s);
  bool mem_rstrcpy(Uint32 addr, char *s);
  bool mem_wbcopy(Uint32 addr, Sint32 *buffer, int size);
  bool mem_rbcopy(Uint32 addr, Sint32 *buffer, int size);
  
	// Slave Interface
	bus_status Read(Uint32 addr, Uint32 *value);
	bus_status Write(Uint32 addr, Uint32 *value);

  unsigned int start_address() const;
  unsigned int end_address() const;

  	/* generic memory access function, it's safe because alignments and permissions
	are checked, handles any natural transfer sizes; note, faults out if nbytes
	is not a power-of-two or larger then MD_PAGE_SIZE */
	fault_t MemAccess(enum MemCmd cmd,		/* Read (from sim mem) or Write */
		Uint32 addr,		/* target address to access */
		void *vp,			/* host memory address to access */
		int nbytes);		/* number of bytes to access */
	
	fault_t MemStrcpy(enum MemCmd cmd,		/* Read (from sim mem) or Write */
	   Uint32 addr,		    /* target address to access */
	   char *s);			/* host memory string buffer */

	/* copy NBYTES to/from simulated memory space, returns any faults */
	fault_t MemBcopy(enum MemCmd cmd,		/* Read (from sim mem) or Write */
		Uint32 addr,		/* target address to access */
		void *vp,			/* host memory address to access */
		int nbytes);
	
	/* register memory system-specific statistics */
	void mem_reg_stats(struct stat_sdb_t *sdb);	/* stats data base */

	/* print a block of memory, returns any faults encountered */
	fault_t PrintMem(Uint32 addr,		/* target address to dump */
		int len,			/* number bytes to dump */
		FILE *stream);			/* output stream */

private:
	Uint32 m_start_address;
	Uint32 m_end_address;
	Uint32 m_nr_wait_states;
	int m_wait_count;
	
  	MemObj*_mem;
	/* create a flat memory space */
	struct MemObj *_MemCreate();
	
	/* initialize memory system, call before loader.c */
	void _MemInit();
	/* translate address ADDR in memory space MEM, returns pointer to host page */
	Uint8 *_MemTranslate(Uint32 addr);		/* virtual address to translate */
	/* locate host page for virtual address ADDR, returns NULL if unallocated */
	Uint8 *_MemPage(Uint32 addr);
	/* allocate a memory page */
	void _MemNewPage(Uint32 addr);		/* virtual address to allocate */
	void _ReadByte(Uint32 addr, Uint8 *value);
	void _ReadWord(Uint32 addr, Uint32 *value);
	void _WriteByte(Uint32 addr, Uint8 *value);
	void _WriteWord(Uint32 addr, Uint32 *value);
}; // end class simple_bus_slow_mem

#endif

