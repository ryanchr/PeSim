#ifndef ME_SIM_SAFE_H
#define ME_SIM_SAFE_H
#include "frame_app.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "host.h"
#include "misc.h"
#include "machine.h"
#include "regs.h"
#include "loader.h"
#include "syscall.h"
#include "dlite.h"
#include "options.h"
#include "core_memory.h"
#include "stats.h"
#include "sim.h"
#include "main.h"
#include "itrc.h"
#include "memory.h"
#include "bus_types.h"
#include "bus_non_blocking_if.h"

class CoreArm : public sc_module
{
public:
	sc_in<bool> clk;
	sc_in<bool> irq;
	sc_port<Bus_non_blocking_if> bus_master_port;
	Uint32 irq_state;
	void MainAction();
	void IrqAction();
	
	SC_HAS_PROCESS(CoreArm);
	
	CoreArm(sc_module_name name
		, Bus_slow_mem *slow_mem
		, Uint32 unique_priority) 
		: sc_module(name)
		,_slow_mem(slow_mem)
		,_unique_priority(unique_priority)
	{
		irq_state = 0;
		SC_THREAD(MainAction);
		sensitive << clk.pos();
		SC_METHOD(IrqAction);
		sensitive << clk.pos();
	}
	
	void PrintState();
	
private:
	md_inst_t inst;
	Bus_slow_mem * _slow_mem;	/*point to the memory of thr top system*/
	Uint32 _unique_priority;
	void _IrqHandler();
	
	void _FetchInst(Uint32 address, Uint32 *value);
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
	
	Uint8 _ReadByte(Uint32 address);
	Uint16 _ReadHalf(Uint32 address);
	Uint32 _ReadWord(Uint32 address);
	Uint64 _ReadQword(Uint64 address);

	void _WriteByte(Uint32 address, Uint8 value);
	void _WriteHalf(Uint32 address, Uint16 value);
	void _WriteWord(Uint32 address, Uint32 value);
	void _WriteQword(Uint32 address, Uint64 value);
};

#endif