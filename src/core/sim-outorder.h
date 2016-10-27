#ifndef ME_SIM_OUTORDER_H
#define ME_SIM_OUTORDER_H
#include "frame_app.h"
#include "machine.h"
#include "cache.h"
#include "memory.h"
#include "itrc.h"
#include "bus_types.h"
#include "bus_non_blocking_if.h"
#include "core_memory.h"



#define ADWATTCH 

// int RUU_size;
//extern int LSQ_size;
//extern int data_width;
//extern int res_ialu;
//extern int res_fpalu;
//extern int res_memport;

//extern  int bimod_config[];

//extern struct cache_t *cache_dl1;
//extern struct cache_t *cache_il1;
//extern struct cache_t *cache_dl2;
//extern struct cache_t *cache_il2;

//extern struct cache_t *dtlb;
//extern struct cache_t *itlb;

//extern char *cache_dl1_opt;
//extern char *cache_dl2_opt;
//extern char *cache_il1_opt;
//extern char *cache_il2_opt;
//extern char *itlb_opt;
//extern char *dtlb_opt;

/* 2-level predictor config (<l1size> <l2size> <hist_size> <xor>) */
//extern int twolev_config[];

/* combining predictor config (<meta_table_size> */
//extern int comb_config[];

/* return address stack (RAS) size */
//extern int ras_size;

/* BTB predictor config (<num_sets> <associativity>) */
//extern int btb_config[];

extern counter_t rename_access;
extern counter_t bpred_access;
extern counter_t window_access;
extern counter_t lsq_access;
extern counter_t regfile_access;
extern counter_t icache_access;
extern counter_t dcache_access;
extern counter_t dcache2_access;

extern counter_t itlb_access;
extern counter_t dtlb_access;

extern counter_t alu_access;
extern counter_t ialu_access;
extern counter_t falu_access;
extern counter_t resultbus_access;

extern counter_t window_selection_access;
extern counter_t window_wakeup_access;
extern counter_t window_preg_access;
extern counter_t lsq_preg_access;
extern counter_t lsq_wakeup_access;
extern counter_t lsq_store_data_access;
extern counter_t lsq_load_data_access;

extern counter_t window_total_pop_count_cycle;
extern counter_t window_num_pop_count_cycle;
extern counter_t lsq_total_pop_count_cycle;
extern counter_t lsq_num_pop_count_cycle;
extern counter_t regfile_total_pop_count_cycle;
extern counter_t regfile_num_pop_count_cycle;
extern counter_t resultbus_total_pop_count_cycle;
extern counter_t resultbus_num_pop_count_cycle;

#ifdef ADWATTCH
/*
extern qword_t    icache_decaddr_hd;
extern qword_t    icache_tagaddr_hd;
extern qword_t    icache_inst_hd;
extern qword_t    tot_icache_decaddr_hd;
extern qword_t    tot_icache_tagaddr_hd;
extern qword_t    tot_icache_inst_hd;
extern qword_t    icache2_decaddr_hd;
extern qword_t    icache2_tagaddr_hd;
extern qword_t    icache2_inst_hd;
extern qword_t    dcache_decaddr_hd;
extern qword_t    dcache_tagaddr_hd;
extern qword_t    dcache_data_hd;
extern qword_t    tot_dcache_decaddr_hd;
extern qword_t    tot_dcache_tagaddr_hd;
extern qword_t    tot_dcache_data_hd;
extern qword_t    dcache2_decaddr_hd;
extern qword_t    dcache2_tagaddr_hd;
extern qword_t    dcache2_data_hd;
*/
qword_t get_hd_decaddr(struct cache_t *cache, md_addr_t prev_addr, md_addr_t curr_addr);
qword_t get_hd_tagaddr(struct cache_t *cache, md_addr_t prev_addr, md_addr_t curr_addr);
qword_t get_hd_btb_decaddr( int btb_config[], md_addr_t prev_addr, md_addr_t curr_addr);
qword_t get_hd_btb_tagaddr( int btb_config[], md_addr_t prev_addr, md_addr_t curr_addr);

qword_t get_hd_inst(md_inst_t prev_inst, md_inst_t curr_inst);
qword_t get_hd_data(word_t prev_data, word_t curr_data);
qword_t get_hd_btaddr(md_addr_t prev_btaddr, md_addr_t curr_btaddr);

void icache_power_hd(md_addr_t icache_access_addr, md_inst_t icache_inst);
void dcache_power_hd(md_addr_t dcache_access_addr, enum mem_cmd cmd );
void btb_power_hd(md_addr_t curr_btb_addr, md_addr_t curr_btaddr, enum mem_cmd cmd);
void icache2_power_hd(void);
void dcache2_power_hd(void);
#endif

#define WATTCH

class CoreArm : public sc_module
{
public:
	sc_in<bool> clk;
	sc_in<bool> irq;
	sc_port<Bus_non_blocking_if> bus_master_port;
	Uint32 irq_state;
      	float local_ipc;
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
		irq_state=0;
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
	void _RuuDispatch(void);
	void _RuuFetch(void);
	void _FetchInst(Uint32 address, Uint32 *value);
	/* generic memory access function, it's safe because alignments and permissions
	are checked, handles any natural transfer sizes; note, faults out if nbytes
	is not a power-of-two or larger then MD_PAGE_SIZE */
	fault_t MemAccess(enum MemCmd cmd,		/* Read (from sim mem) or Write */
		Uint32 addr,		/* target address to access */
		void *vp,			/* host memory address to access */
		int nbytes);		/* number of bytes to access */

	fault_t _SpecMemAccess(	enum MemCmd cmd,		/* Read or Write access cmd */
		Uint32 addr,			/* virtual address of access */
		void *p,			/* input/output buffer */
		int nbytes);			/* number of bytes to access */

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
