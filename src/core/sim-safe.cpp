/*
 * sim-safe.c - functional simulator implementation
 *
 * This file is a part of the SimpleScalar tool suite written by
 * Todd M. Austin as a part of the Multiscalar Research Project.
 *  
 * The tool suite is currently maintained by Doug Burger and Todd M. Austin.
 * 
 * Copyright (C) 1994, 1995, 1996, 1997, 1998 by Todd M. Austin
 *
 * This source file is distributed "as is" in the hope that it will be
 * useful.  The tool set comes with no warranty, and no author or
 * distributor accepts any responsibility for the consequences of its
 * use. 
 * 
 * Everyone is granted permission to copy, modify and redistribute
 * this tool set under the following conditions:
 * 
 *    This source code is distributed for non-commercial use only. 
 *    Please contact the maintainer for restrictions applying to 
 *    commercial use.
 *
 *    Permission is granted to anyone to make or distribute copies
 *    of this source code, either as received or modified, in any
 *    medium, provided that all copyright notices, permission and
 *    nonwarranty notices are preserved, and that the distributor
 *    grants the recipient permission for further redistribution as
 *    permitted by this document.
 *
 *    Permission is granted to distribute this file in compiled
 *    or executable form under the same conditions that apply for
 *    source code, provided that either:
 *
 *    A. it is accompanied by the corresponding machine-readable
 *       source code,
 *    B. it is accompanied by a written offer, with no time limit,
 *       to give anyone a machine-readable copy of the corresponding
 *       source code in return for reimbursement of the cost of
 *       distribution.  This written offer must permit verbatim
 *       duplication by anyone, or
 *    C. it is distributed by someone who received only the
 *       executable form, and is accompanied by a copy of the
 *       written offer of source code that they received concurrently.
 *
 * In other words, you are welcome to use, share and improve this
 * source file.  You are forbidden to forbid anyone else to use, share
 * and improve what you give them.
 *
 * INTERNET: dburger@cs.wisc.edu
 * US Mail:  1210 W. Dayton Street, Madison, WI 53706
 *
 * $Id: sim-safe.c,v 1.1.1.1 2000/11/29 14:53:54 cu-cs Exp $
 *
 * $Log: sim-safe.c,v $
 * Revision 1.1.1.1  2000/11/29 14:53:54  cu-cs
 * Grand unification of arm sources.
 *
 *
 * Revision 1.1.1.1.2.11  2000/11/04 05:30:23  taustin
 * Cleaned up the code.
 *
 * Revision 1.1.1.1.2.10  2000/09/19 17:25:32  taustin
 * Completed UOP decomposition code, all UOPs now take nominally one cycle on a
 * simple pipeline, including loads and stores.  Initial testing has the code
 * working fine, however, extensive random testing will occur when sim-fuzz.c
 * gets extended to support multiple functional units...
 *
 * Revision 1.1.1.1.2.9  2000/09/05 13:56:02  taustin
 * SimpleScalar/ARM fuzz buster - random co-simulation tester, very handy!
 *
 * Revision 1.1.1.1.2.8  2000/08/30 21:23:39  taustin
 * Fixed r15 update semantics (now catches r15 updated to value of PC, this happens
 * when a tail recursive function returns to itself - oye!)...
 *
 * Revision 1.1.1.1.2.7  2000/08/29 14:18:09  taustin
 * Fixed word and qword size fp register accesses.
 *
 * Revision 1.1.1.1.2.6  2000/08/26 21:04:14  taustin
 * Added -trigger:inst <N> option to enable verbose dumps mid-execution.
 *
 * Revision 1.1.1.1.2.5  2000/08/26 06:53:53  taustin
 * Simplified SimpleScalar/ARM PC handling - seems to work...
 *
 * Revision 1.1.1.1.2.4  2000/08/22 18:38:49  taustin
 * More progress on the SimpleScalar/ARM target.
 *
 * Revision 1.1.2.3  2000/08/12 20:15:29  taustin
 * Fixed loader problems.
 * Improved heap management.
 * Added improved bogus address checks.
 *
 * Revision 1.1.2.2  2000/08/02 09:44:54  taustin
 * Fixed stat system call emulation.
 *
 * Revision 1.1.2.1  2000/08/02 08:51:57  taustin
 * SimpleScalar/ARM co-simulation component, based on the ARMulator.
 *
 * Revision 1.1.1.1.2.3  2000/07/28 21:37:08  taustin
 * Added ld_text_bound and ld_data_bound to loader exports.
 *
 * Revision 1.1.1.1.2.2  2000/07/26 05:01:32  taustin
 * Added more debug output.
 *
 * Revision 1.1.1.1.2.1  2000/07/21 18:30:55  taustin
 * More progress on the SimpleScalar/ARM target.
 *
 * Revision 1.1.1.1  2000/05/26 15:18:58  taustin
 * SimpleScalar Tool Set
 *
 *
 * Revision 1.9  1999/12/31 18:53:24  taustin
 * quad_t naming conflicts removed
 *
 * Revision 1.8  1999/12/13 18:47:13  taustin
 * cross endian execution support added
 *
 * Revision 1.7  1998/08/31 17:11:01  taustin
 * added register checksuming support, viewable with "-v" flag
 *
 * Revision 1.6  1998/08/27 16:38:25  taustin
 * implemented host interface description in host.h
 * added target interface support
 * added support for register and memory contexts
 * instruction predecoding moved to loader module
 * Alpha target support added
 * added support for qword's
 * added fault support
 * added option ("-max:inst") to limit number of instructions analyzed
 * added target-dependent myprintf() support
 *
 * Revision 1.5  1997/03/11  17:14:57  taustin
 * updated copyright
 * long/int tweaks made for ALPHA target support
 * supported added for non-GNU C compilers
 *
 * Revision 1.4  1997/01/06  16:06:28  taustin
 * updated comments
 * opt_reg_header() call now prints simulator overview message
 * access variable now generalized to is_write boolean flag
 *
 * Revision 1.3  1996/12/27  15:54:04  taustin
 * updated comments
 * integrated support for options and stats packages
 * added sim_init() code
 *
 * Revision 1.1  1996/12/05  18:52:32  taustin
 * Initial revision
 *
 *
 */
#include "sim-safe.h"
/*
 * This file implements a functional simulator.  This functional simulator is
 * the simplest, most user-friendly simulator in the simplescalar tool set.
 * Unlike sim-fast, this functional simulator checks for all instruction
 * errors, and the implementation is crafted for clarity rather than speed.
 */

extern FILE *fout;

/* simulated registers */
static struct regs_t regs;
static struct regs_t regs_sys;
static struct regs_t regs_irq;

/* simulated memory */
static struct mem_t *mem = NULL;


/* current processor mode */
enum CoreMode{ 
	mode_user=0, 
	mode_fiq,
	mode_svc,
	mode_abt,
	mode_irq,
	mode_und,
	mode_MAX}pmode;
#define NOMODE (enum CoreMode)-1
enum CoreMode msk2mode[32] =
  { NOMODE, NOMODE, NOMODE, NOMODE, NOMODE, NOMODE, NOMODE, NOMODE, 
  	NOMODE, NOMODE, NOMODE, NOMODE, NOMODE, NOMODE, NOMODE, NOMODE,
    mode_user, mode_fiq, mode_irq, mode_svc, NOMODE, NOMODE, NOMODE, mode_abt,
    NOMODE, NOMODE, NOMODE, mode_und, NOMODE, NOMODE, NOMODE, NOMODE };

char *mode2str[6] =
  { "user", "fiq", "svc", "abt", "irq", "undef" };


/* simulation fault list */
/* Must be global to be accessible by faulting devices / existing memory system, etc ?*/
/* **MAY** be better to start passing this as argument by convention? */
#define FAULT_GROUP	0
#define FAULT_EXISTS	0//(flt_check(0))
#define GET_FIRST_FAULT  //(flt_get_first(0))
#define MEMORY_FAULT_GROUP	0	/* Needed for memory access macros...*/
#define FAULT_ACTION		;//goto fault_handler   /* used in machine.def when function returns fault */

/* Interrupt Controller */
struct ITC_state *IController;	/* Pointer to Interrupt Controller */

/* track number of refs */
static counter_t sim_num_refs = 0;


/* maximum number of inst's to execute */
static unsigned int max_insts;

static unsigned int trigger_inst;
static unsigned int trigger_addr;
static md_addr_t trigger_word;
int irq_debug;

/* register simulator-specific options */
void
sim_reg_options(struct opt_odb_t *odb)
{
  opt_reg_header(odb, 
"sim-safe: This simulator implements a functional simulator.  This\n"
"functional simulator is the simplest, most user-friendly simulator in the\n"
"simplescalar tool set.  Unlike sim-fast, this functional simulator checks\n"
"for all instruction errors, and the implementation is crafted for clarity\n"
"rather than speed.\n"
		 );

  /* instruction limit */
  opt_reg_uint(odb, "-max:inst", "maximum number of inst's to execute",
	       &max_insts, /* default */0,
	       /* print */TRUE, /* format */NULL);

  opt_reg_uint(odb, "-trigger:inst", "trigger instruction",
	       &trigger_inst, /* default */0,
	       /* print */TRUE, /* format */NULL);
	
	opt_reg_uint(odb, "-trigger:addr", "trigger address",
	  	&trigger_addr, /* default */0,
	  	/* print */TRUE, /* format */NULL);
	
	opt_reg_uint(odb, "-trigger:word", "trigger watch word",
	  	&trigger_word, /* default */0,
	  	/* print */TRUE, /* format */NULL);
	
	 opt_reg_flag(odb, "-irq:debug", "turn on IRQ debug messages",
	 	&irq_debug, /* default */FALSE,
	 	/* print */TRUE, /* format */NULL);
}

/* check simulator-specific option values */
void
sim_check_options(struct opt_odb_t *odb, int argc, char **argv)
{
  /* nada */
}

/* register simulator-specific statistics */
void
sim_reg_stats(struct stat_sdb_t *sdb)
{
  stat_reg_counter(sdb, "sim_num_insn",
		   "total number of instructions executed",
		   &sim_num_insn, sim_num_insn, NULL);
  stat_reg_counter(sdb, "sim_num_refs",
		   "total number of loads and stores executed",
		   &sim_num_refs, 0, NULL);
  stat_reg_int(sdb, "sim_elapsed_time",
	       "total simulation time in seconds",
	       &sim_elapsed_time, 0, NULL);
  stat_reg_formula(sdb, "sim_inst_rate",
		   "simulation speed (in insts/sec)",
		   "sim_num_insn / sim_elapsed_time", NULL);
  ld_reg_stats(sdb);
  mem_reg_stats(mem, sdb);
}


/* register MAPS */
word_t *vregR[mode_MAX][16];
word_t *vregC[mode_MAX];
word_t *vregS[mode_MAX];

/* initialize the simulator */
void
sim_init(void)
{
	int i, j;
  sim_num_refs = 0;

  /* allocate and initialize register file */
  regs_init(&regs);
	regs_init(&regs_sys);
	regs_init(&regs_irq);
	

  /* allocate and initialize memory space */
  mem = mem_create("mem");
  mem_init(mem);
	IController = ITC_init();
	/* build the register map */
	for (i=mode_user; i <= mode_und; i++)
	{
		for (j=0; j < 16; j++)
			vregR[i][j] = &regs.regs_R[j];
    }
	for (i=mode_user; i <= mode_und; i++)
		vregC[i] = &regs.regs_C.cpsr;

	vregS[mode_user] = NULL;
	vregS[mode_fiq] = &regs.regs_BANK.FIQ_SPSR;
	vregS[mode_svc] = &regs.regs_BANK.SVC_SPSR;
	vregS[mode_abt] = &regs.regs_BANK.ABT_SPSR;
	vregS[mode_irq] = &regs.regs_BANK.IRQ_SPSR;
	vregS[mode_und] = &regs.regs_BANK.UND_SPSR;

	/* register map overrides */
	for (j=8,i=0; j <= 14; j++,i++)
		vregR[mode_fiq][j] = &regs.regs_BANK.FIQ_REGS[i];
	for (j=13,i=0; j <= 14; j++,i++)
		vregR[mode_svc][j] = &regs.regs_BANK.SVC_REGS[i];
	for (j=13,i=0; j <= 14; j++,i++)
		vregR[mode_abt][j] = &regs.regs_BANK.ABT_REGS[i];
	for (j=13,i=0; j <= 14; j++,i++)
		vregR[mode_irq][j] = &regs.regs_BANK.IRQ_REGS[i];
	for (j=13,i=0; j <= 14; j++,i++)
		vregR[mode_und][j] = &regs.regs_BANK.UND_REGS[i];
}

/* load program into simulated state */
void
sim_load_prog(char *fname,		/* program to load */
	      int argc, char **argv,	/* program arguments */
			  char **envp, 		/* program environment */
			  Bus_slow_mem *mem_slow)
{
  /* load program text and data, set up environment, memory, and regs */
	ld_load_prog(fname, argc, argv, envp, &regs, mem, TRUE, mem_slow);

  /* initialize the DLite debugger */
  dlite_init(md_reg_obj, dlite_mem_obj, dlite_mstate_obj);
}

/* print simulator-specific configuration information */
void
sim_aux_config(FILE *stream)		/* output stream */
{
  /* nothing currently */
}

/* dump simulator-specific auxiliary simulator statistics */
void
sim_aux_stats(FILE *stream)		/* output stream */
{
  /* nada */
}

/* un-initialize simulator-specific state */
void
sim_uninit(void)
{
  /* nada */
}


/*
 * configure the execution engine
 */

/*
 * precise architected register accessors
 */

/* next program counter */
#define SET_NPC(EXPR)		(regs.regs_NPC = (EXPR))

/* current program counter */
#define CPC			(regs.regs_PC)

/* general purpose registers */
//#define GPR(N)			(regs.regs_R[N])
//#define SET_GPR(N,EXPR)							\
//	((void)(((N) == 15) ? setPC++ : 0), regs.regs_R[N] = (EXPR))
/* general purpose registers */
#define GPR(N)			(*(vregR[pmode][N]))
#define SET_GPR(N,EXPR)							\
	((void)(((N) == 15) ? setPC++ : 0), (*(vregR[pmode][N])) = (EXPR))
  
#if defined(TARGET_PISA)

/* floating point registers, L->word, F->single-prec, D->double-prec */
#define FPR_L(N)		(regs.regs_F.l[(N)])
#define SET_FPR_L(N,EXPR)	(regs.regs_F.l[(N)] = (EXPR))
#define FPR_F(N)		(regs.regs_F.f[(N)])
#define SET_FPR_F(N,EXPR)	(regs.regs_F.f[(N)] = (EXPR))
#define FPR_D(N)		(regs.regs_F.d[(N) >> 1])
#define SET_FPR_D(N,EXPR)	(regs.regs_F.d[(N) >> 1] = (EXPR))

/* miscellaneous register accessors */
#define SET_HI(EXPR)		(regs.regs_C.hi = (EXPR))
#define HI			(regs.regs_C.hi)
#define SET_LO(EXPR)		(regs.regs_C.lo = (EXPR))
#define LO			(regs.regs_C.lo)
#define FCC			(regs.regs_C.fcc)
#define SET_FCC(EXPR)		(regs.regs_C.fcc = (EXPR))

#elif defined(TARGET_ALPHA)

/* floating point registers, L->word, F->single-prec, D->double-prec */
#define FPR_Q(N)		(regs.regs_F.q[N])
#define SET_FPR_Q(N,EXPR)	(regs.regs_F.q[N] = (EXPR))
#define FPR(N)			(regs.regs_F.d[(N)])
#define SET_FPR(N,EXPR)		(regs.regs_F.d[(N)] = (EXPR))
/* miscellaneous register accessors */
#define SET_HI(EXPR)		(regs.regs_C.hi = (EXPR))
#define HI			(regs.regs_C.hi)
#define SET_LO(EXPR)		(regs.regs_C.lo = (EXPR))
#define LO			(regs.regs_C.lo)
#define FCC			(regs.regs_C.fcc)
#define SET_FCC(EXPR)		(regs.regs_C.fcc = (EXPR))

/* miscellaneous register accessors */
#define FPCR			(regs.regs_C.fpcr)
#define SET_FPCR(EXPR)		(regs.regs_C.fpcr = (EXPR))
#define UNIQ			(regs.regs_C.uniq)
#define SET_UNIQ(EXPR)		(regs.regs_C.uniq = (EXPR))

#elif defined(TARGET_ARM)

/* processor status register */
#define CP15(N)                 (*(regs.regs_CP15[N]))
#define SET_CP15(N, EXPR)     \
  ((void)(((N) == 1) ? (setCP15 = (N)) : 0), (*(regs.regs_CP15[N])) = EXPR)
  
#define PSR			(regs.regs_C.cpsr)
#define SET_PSR(EXPR)							\
  ((((PSR_MODE) == USER_MODE) 					\
	  ? (regs.regs_C.cpsr = ((regs.regs_C.cpsr & ~(0x0f << 28))	\
				 | ((EXPR) & (0x0f << 28))))		\
	  : (regs.regs_C.cpsr = (EXPR))))
/*
#define SET_PSR(EXPR)	\
	if((PSR_MODE) == USER_MODE)\
	{		\
		regs.regs_C.cpsr = ((regs.regs_C.cpsr & ~(0x0f << 28)) | ((EXPR) & (0x0f << 28)));\
	}\
	else	\
	{	\
		if (((EXPR)&0x1f) != (regs.regs_C.cpsr&0x1f))\
		{	\
		}	\
		regs.regs_C.cpsr = (EXPR);	\
	}
*/
#define PSR_N			_PSR_N(regs.regs_C.cpsr)
#define SET_PSR_N(EXPR)		_SET_PSR_N(regs.regs_C.cpsr, (EXPR))
#define PSR_C			_PSR_C(regs.regs_C.cpsr)
#define SET_PSR_C(EXPR)		_SET_PSR_C(regs.regs_C.cpsr, (EXPR))
#define PSR_Z			_PSR_Z(regs.regs_C.cpsr)
#define SET_PSR_Z(EXPR)		_SET_PSR_Z(regs.regs_C.cpsr, (EXPR))
#define PSR_V			_PSR_V(regs.regs_C.cpsr)
#define SET_PSR_V(EXPR)		_SET_PSR_V(regs.regs_C.cpsr, (EXPR))

#define PSR_MODE                _PSR_MODE(regs.regs_C.cpsr)
#define PSR_IRQ			_PSR_IRQ(regs.regs_C.cpsr)
#define SET_PSR_IRQ(VAL)       	_SET_PSR_IRQ(regs.regs_C.cpsr, VAL)
#define PSR_FIQ			_PSR_FIQ(regs.regs_C.cpsr)
#define SET_PSR_FIQ(VAL)	_SET_PSR_FIQ(regs.regs_C.cpsr, VAL)

#define SPSR			get_SPSR()
word_t get_SPSR()
{
  switch(PSR_MODE) {
  case USER_MODE:
    fatal("Attempt to access (read) SPSR register in USER mode @ 0x0%08p", regs.regs_PC);
  case FIQ_MODE:
    return regs.regs_BANK.FIQ_SPSR;
  case IRQ_MODE:
    return regs.regs_BANK.IRQ_SPSR;
  case SVC_MODE:
    return regs.regs_BANK.SVC_SPSR;
  case ABT_MODE:
    return regs.regs_BANK.ABT_SPSR;
  case UND_MODE:
    return regs.regs_BANK.UND_SPSR;
  default:
    fatal("Bogus current mode when retrieving SPSR @ 0x0%08p", regs.regs_PC);
  }
  return 0;
}


#define SET_SPSR(EXPR)		set_SPSR((word_t)(EXPR));
void set_SPSR(word_t val)
{
  switch(PSR_MODE) {
  case USER_MODE:
    fatal("Attempt to access (write) SPSR register in USER mode @ 0x0%08p", regs.regs_PC);
  case FIQ_MODE:
    regs.regs_BANK.FIQ_SPSR = val;
    break;
  case IRQ_MODE:
    regs.regs_BANK.IRQ_SPSR = val;
    break;
  case SVC_MODE:
    regs.regs_BANK.SVC_SPSR = val;
    break;
  case ABT_MODE:
    regs.regs_BANK.ABT_SPSR = val;
    break;
  case UND_MODE:
    regs.regs_BANK.UND_SPSR = val;
    break;
  default:
    fatal("Bogus current mode when setting SPSR @ 0x0%08p", regs.regs_PC);
  }
  return;
}


/* Change processor mode: NOTE:::  use RESTORE_PSR_MODE restore previous mode!! */
#define SET_PSR_MODE(MODE, PC, NPC)  SET_MODE(MODE, PC, NPC)

/* Restore previous mode: Note: DOES NOT restore PC!!!!  Assumes write to R15 covers it!!!! */
#define RESTORE_PSR_MODE    restore_mode()

#define SWAP_MODE_REGS(NEW_MODE)									\
do{													\
  if(NEW_MODE##_MODE == USER_MODE) fatal("CODING ERROR: File [%s], ~Line [%d]:"				\
				 "Cannot SET_PSR to user mode, can only restore to user mode.",		\
				 __FILE__, __LINE__);							\
  switch(PSR_MODE) {											\
  case USER_MODE:											\
    fatal("USER mode switches are whack");											\
    /*_SWAP_MODE_REGS(USER, NEW_MODE, regs.regs_R, regs.regs_BANK);*/  /* swap to banked registers */	\
    break;												\
  case FIQ_MODE:											\
    /*_SWAP_MODE_REGS(FIQ, NEW_MODE, regs.regs_R, regs.regs_BANK);*/  /* swap to banked registers */	\
    break;												\
  case IRQ_MODE:											\
    /*_SWAP_MODE_REGS(IRQ, NEW_MODE, regs.regs_R, regs.regs_BANK);*/  /* swap to banked registers */	\
    break;												\
  case SVC_MODE:											\
    /*_SWAP_MODE_REGS(SVC, NEW_MODE, regs.regs_R, regs.regs_BANK);*/  /* swap to banked registers */	\
    break;												\
  case ABT_MODE:											\
    /*_SWAP_MODE_REGS(ABT, NEW_MODE, regs.regs_R, regs.regs_BANK);*/  /* swap to banked registers */	\
    break;												\
  case UND_MODE:											\
    /*_SWAP_MODE_REGS(UND, NEW_MODE, regs.regs_R, regs.regs_BANK);*/  /* swap to banked registers */	\
    break;												\
  default:												\
    fatal("in: SWAP_MODE_REGS - invalid current mode!!");						\
  }													\
} while (0)
														      
#define SET_MODE(NEWMODE, PC, NPC)  /* MODE to switch to, and PC to be saved  (w/ +4/+8 already included)  */		\
do{														\
  if (irq_debug)							\
    myfprintf(stderr, "*MODE* switching to mode `%s'...\n",		\
            (NEWMODE##_MODE == USER_MODE) ? "user"			\
            : (NEWMODE##_MODE == FIQ_MODE) ? "fiq"			\
	    : (NEWMODE##_MODE == IRQ_MODE) ? "irq"			\
	    : (NEWMODE##_MODE == SVC_MODE) ? "svc"			\
	    : (NEWMODE##_MODE == ABT_MODE) ? "abt"			\
	    : (NEWMODE##_MODE == UND_MODE) ? "und" : "???");		\
  SWAP_MODE_REGS(NEWMODE);				/* Swap mode registers with banked registers */		\
  _STORE_CPSR(regs.regs_C.cpsr, regs.regs_BANK, NEWMODE);  /* store CPSR to appropriate SPSR */			\
  _MODE_SET_CPSR(regs.regs_C.cpsr, NEWMODE);		/* Set CPSR to new mode (affects I/F bits as well) */	\
  pmode = msk2mode[regs.regs_C.cpsr & 0x1f];				\
  SET_GPR(14, NPC);				        /* Store next pc to link register */			\
  PC = _INTERRUPT_VECTOR(NEWMODE);				/* Set next PC to interrupt vector */			\
} while (0)
  	

#define RESTORE_REGS(OLD_MODE)										\
do{													\
  if(OLD_MODE##_MODE == PSR_MODE)					\
    if (irq_debug)							\
      warn("in: restore_mode().RESTORE_REGS : restoring to same mode!!");	\
  switch(PSR_MODE)											\
    {													\
    case USER_MODE:											\
      if (irq_debug) fprintf(stderr, "*MODE* restoring mode to `user'...\n");	\
      /*_SWAP_MODE_REGS(OLD_MODE, USER, regs.regs_R, regs.regs_BANK);*/  /* swap to banked registers */	\
      break;												\
    case FIQ_MODE:											\
      if (irq_debug) fprintf(stderr, "*MODE* restoring mode to `fiq'...\n");	\
      /*_SWAP_MODE_REGS(OLD_MODE, FIQ, regs.regs_R, regs.regs_BANK);*/  /* swap to banked registers */	\
      break;												\
    case IRQ_MODE:											\
      if (irq_debug) fprintf(stderr, "*MODE* restoring mode to `irq'...\n");	\
      /*_SWAP_MODE_REGS(OLD_MODE, IRQ, regs.regs_R, regs.regs_BANK);*/  /* swap to banked registers */	\
      break;												\
    case SVC_MODE:											\
      if (irq_debug) fprintf(stderr, "*MODE* restoring mode to `svc'...\n");	\
      /*_SWAP_MODE_REGS(OLD_MODE, SVC, regs.regs_R, regs.regs_BANK);*/  /* swap to banked registers */	\
      break;												\
    case ABT_MODE:											\
      if (irq_debug) fprintf(stderr, "*MODE* restoring mode to `abt'...\n");	\
      /*_SWAP_MODE_REGS(OLD_MODE, ABT, regs.regs_R, regs.regs_BANK);*/  /* swap to banked registers */	\
      break;												\
    case UND_MODE:											\
      if (irq_debug) fprintf(stderr, "*MODE* restoring mode to `und'...\n");	\
      /*_SWAP_MODE_REGS(OLD_MODE, UND, regs.regs_R, regs.regs_BANK);*/  /* swap to banked registers */	\
      break;												\
    default:												\
      fatal("in: restore_mode - invalid old mode!!");							\
    }													\
}while(0)

void restore_mode()													
{															
  switch(PSR_MODE) 
    {
    case USER_MODE:
      fatal("in: restore_mode(): attempt to restore from USER mode");
      break;
    case FIQ_MODE:
      _LOAD_CPSR(regs.regs_C.cpsr, regs.regs_BANK, FIQ);
      /*  regs.regs_NPC = GPR(14); */
      RESTORE_REGS(FIQ);
      break;
    case IRQ_MODE:
      _LOAD_CPSR(regs.regs_C.cpsr, regs.regs_BANK, IRQ);
      /*  regs.regs_NPC = GPR(14); */
      RESTORE_REGS(IRQ);
      break;
    case SVC_MODE:
      _LOAD_CPSR(regs.regs_C.cpsr, regs.regs_BANK, SVC);
      /*  regs.regs_NPC = GPR(14); */
      RESTORE_REGS(SVC);
      break;
    case ABT_MODE:
      _LOAD_CPSR(regs.regs_C.cpsr, regs.regs_BANK, ABT);
      /*  regs.regs_NPC = GPR(14); */
      RESTORE_REGS(ABT);
      break;
    case UND_MODE:
      _LOAD_CPSR(regs.regs_C.cpsr, regs.regs_BANK, UND);
      /*  regs.regs_NPC = GPR(14); */
      RESTORE_REGS(UND);
      break;														
    default:														
      fatal("in: restore_mode - invalid current mode!!");								
    }
}															
  

/* floating point conversions */
union x { float f; word_t w; };
#define DTOW(D)		({ union x fw; fw.f = (float)(D); fw.w; })
#define WTOD(W)		({ union x fw; fw.w = (W); (double)fw.f; })
#define QSWP(Q)								\
	((((Q) << 32) & ULL(0xffffffff00000000)) | (((Q) >> 32) & ULL(0xffffffff)))

/* floating point registers, L->word, F->single-prec, D->double-prec */
#define FPR_Q(N)		(QSWP(regs.regs_F.q[N]))
#define SET_FPR_Q(N,EXPR)	(regs.regs_F.q[N] = QSWP((EXPR)))
#define FPR_W(N)		(DTOW(regs.regs_F.d[N]))
#define SET_FPR_W(N,EXPR)	(regs.regs_F.d[N] = (WTOD(EXPR)))
#define FPR(N)			(regs.regs_F.d[(N)])
#define SET_FPR(N,EXPR)		(regs.regs_F.d[(N)] = (EXPR))

/* miscellaneous register accessors */
#define FPSR			(regs.regs_C.fpsr)
#define SET_FPSR(EXPR)		(regs.regs_C.fpsr = (EXPR))

#else
#error No ISA target defined...
#endif

void CoreArm::_IrqHandler()
{
	printf("irq||||||||||||||||||||||\n");
	regs.regs_PC = 0x0;
	regs.regs_NPC = regs.regs_PC + sizeof(md_inst_t);
	regs.regs_R[MD_REG_PC] = regs.regs_PC;
	
	/*update the system register file*/
	regs_sys.regs_R[MD_REG_SP] = regs.regs_R[MD_REG_SP];
	regs_sys.regs_R[MD_REG_LR] = regs.regs_R[MD_REG_LR];
	regs_sys.regs_C.spsr = regs.regs_C.spsr;
	
	/*update the ss register file*/
	regs.regs_R[MD_REG_SP] = regs_irq.regs_R[MD_REG_SP];
	regs.regs_R[MD_REG_LR] = regs_irq.regs_R[MD_REG_LR];
	regs.regs_C.spsr = regs_irq.regs_C.spsr;
}

fault_t CoreArm::MemAccess(enum MemCmd cmd, Uint32 addr, void *vp, int nbytes)
{
	Uint32 *pb = (Uint32 *)vp;
	int tmp = nbytes/4;

	/* check alignments */
	if (/* check size, the size must be an even number*/(nbytes & (nbytes-1)) != 0
		|| /* check max size */nbytes > MD_PAGE_SIZE)
		return mem_fault_access;

	if (/* check natural alignment */(addr & (((nbytes > 4) ? 4:nbytes)-1)) != 0)
		return mem_fault_alignment;
	/* perform the copy */
	{
		if (cmd == Read)
		{
			for (int i = 0; i < tmp; i++)
			{
				*pb = _ReadWord(addr);
				addr = addr + 4;
				pb++;	/*pb = pb + 4*/
			}
			if(nbytes%4)
			{
				fatal("CoreArm::MemAccess have not finished\n");
			}
		}
		else
		{
			for (int i = 0; i < tmp; i++)
			{
				_WriteWord(addr, *pb);
				addr = addr + 4;
				pb++;	/*pb = pb + 4*/
			}
			if(nbytes%4)
			{
				fatal("CoreArm::MemAccess have not finished\n");
			}
		}
	}
	/* no fault... */
	return mem_fault_none;
}


void CoreArm::_FetchInst(Uint32 address, Uint32 * value)
{
	bus_master_port->Read(_unique_priority, value, address);
	while ((bus_master_port->get_status(_unique_priority) != BUS_OK) &&
		(bus_master_port->get_status(_unique_priority) != BUS_ERROR))
	{
		wait();
	}


	if (bus_master_port->get_status(_unique_priority) == BUS_ERROR)
	{
		fatal("%g %s : ERROR cannot read from %x\n", 
			sc_time_stamp().to_double(), name(), address);
	}

	//_slow_mem->direct_read((Sint32*)&inst, regs.regs_PC);
}

Uint8 CoreArm::_ReadByte(Uint32 address)
{
	#if 0
	Uint8 data8;
	_slow_mem->MemAccess(CmdRead, address, &data8, 1);
	return data8;
	#endif
	Uint8 data8;
	Uint32 data32;
	Uint32 addr_align;
	addr_align = address & 0xfffffffc; /*align the address*/

	bus_master_port->Read(_unique_priority, &data32, addr_align);

	while ((bus_master_port->get_status(_unique_priority) != BUS_OK) &&
		(bus_master_port->get_status(_unique_priority) != BUS_ERROR))
	{
		wait();
	}

	if (bus_master_port->get_status(_unique_priority) == BUS_ERROR)
	{
		fatal("%g %s : ERROR cannot________ read from %x\n",
			sc_time_stamp().to_double(), name(), address);
	}
	Uint8 *tmp;
	tmp = (Uint8 *)&data32;
	data8 = (Uint8)tmp[address - addr_align]; 
	fprintf(fout, "READ_BYTE DST = 0x%x	MEM_READ_BYTE = 0x%x\n", address, data8);
	return data8;
}

Uint16 CoreArm::_ReadHalf(Uint32 address)
{
	#if 0
	Uint16 data16;
	_slow_mem->MemAccess(CmdRead, address, &data16, 2);
	return data16;
	#endif
	
	Uint16 data16;
	Uint32 data32;
	Uint32 addr_align;
	addr_align = address & 0xfffffffc; /*align the address*/
	bus_master_port->Read(_unique_priority, &data32, addr_align);

	while ((bus_master_port->get_status(_unique_priority) != BUS_OK) &&
		(bus_master_port->get_status(_unique_priority) != BUS_ERROR))
	{
		wait();
	}

	if (bus_master_port->get_status(_unique_priority) == BUS_ERROR)
	{
		fatal("%g %s : ERROR cannot________ read from %x\n",
			sc_time_stamp().to_double(), name(), address);
	}

	Uint16 *tmp;
	tmp = (Uint16 *)&data32;
	data16 = (Uint16)tmp[address - addr_align]; 
	fprintf(fout, "READ_HALF DST = 0x%x	MEM_READ_WORD = 0x%x\n", address, data16);
	return data16;
}

Uint32 CoreArm::_ReadWord(Uint32 address)
{
	#if 0
	Uint32 data32;
	_slow_mem->MemAccess(CmdRead, address, &data32, 4);
	return data32;
	#endif
	Uint32 value;
	bus_master_port->Read(_unique_priority, &value, address);

	while ((bus_master_port->get_status(_unique_priority) != BUS_OK) &&
		(bus_master_port->get_status(_unique_priority) != BUS_ERROR))
		wait();

	if (bus_master_port->get_status(_unique_priority) == BUS_ERROR)
		fatal("%g %s : ERROR cannot________ read from %x\n",
		sc_time_stamp().to_double(), name(), address);
	fprintf(fout, "READ_WORD DST = 0x%x	MEM_READ_WORD = 0x%x\n", address, value);
	return value;
	
}

Uint64 CoreArm::_ReadQword(Uint64 address)
{
	fatal("_ReadQword undefined\n");
	return 0;
}

void CoreArm::_WriteByte(Uint32 address, Uint8 value)
{
	_slow_mem->MemAccess(CmdWrite, address, &value, 1);
	#if 0
	fprintf(fout, "WRITE_BYTE DST = 0x%x	MEM_WRITE_WORD = 0x%x\n", address, value);
	Uint8 data8;
	Uint32 data32;
	Uint32 addr_align;
	addr_align = address & 0xfffffffc; /*align the address*/


	_slow_mem->MemAccess(CmdRead, addr_align, &data32, 4);
	Uint8 *tmp;
	tmp = (Uint8 *)&data32;
	tmp[address - addr_align] = value;
	_slow_mem->MemAccess(CmdWrite, addr_align, &data32, 4);	
	#endif

}

void CoreArm::_WriteHalf(Uint32 address, Uint16 value)
{
	//fatal("_WriteHalf undefined, address = 0x%x\n, address");
	_slow_mem->MemAccess(CmdWrite, address, &value, 2);
}

void CoreArm::_WriteWord(Uint32 address, Uint32 value)
{
	#if 0
	_slow_mem->MemAccess(CmdWrite, address, &value, 4);
	#endif
	fprintf(fout, "WRITE_WORD DST = 0x%x	MEM_WRITE_WORD = 0x%x\n", address, value);
	bus_master_port->Write(_unique_priority, &value, address);

	while ((bus_master_port->get_status(_unique_priority) != BUS_OK) &&
		(bus_master_port->get_status(_unique_priority) != BUS_ERROR))
	{
		wait();
	}

	if (bus_master_port->get_status(_unique_priority) == BUS_ERROR)
	{
		fatal("%g %s : ERROR cannot write to %x\n",
			sc_time_stamp().to_double(), name(), address);
	}
	
}

void CoreArm::_WriteQword(Uint32 address, Uint64 value)
{
	fatal("_WriteQword undefined, address = 0x%x\n, address");
}

void CoreArm::PrintState()
{
	Uint32 _inst;
	_slow_mem->MemAccess(CmdRead, regs.regs_PC, &_inst, 4);
	md_print_insn(_inst, regs.regs_PC, stderr);
	fprintf(stderr, "   (PC = 0x%08x  inst = 0x%08x)\n", regs.regs_PC, _inst);	
	md_print_iregs(regs.regs_R, stderr);
}

void CoreArm::IrqAction()
{
	if (irq == 1)
	{
		printf("Core received an IRQ\n");
		irq_state = 1;
	}
}
/* start simulation, program loaded, processor precise state initialized */
void CoreArm::MainAction()
{
	irq_state = 0;
  register md_addr_t addr;
  enum md_opcode op;
  register int is_write;
	enum mem_fault_type fault;
	int trapPC = FALSE;
	int setPC, setCP15;

  fprintf(stderr, "sim: ** starting functional simulation **\n");

	/* Set up initial architected environment */
	/* Some notes:  1. No assumptions should be made about contents of registers
                     so there is no need to force values, (should all be 0 anyway)
	*/
	regs.regs_C.cpsr = SVC_MODE;   /* Set supervisor mode */
	SET_PSR_IRQ(1);		 /* Block IRQ and FIQ interrupts */
	SET_PSR_FIQ(1);
  
  /* set up initial default next PC */
  regs.regs_NPC = regs.regs_PC + sizeof(md_inst_t);

  /* synchronize register files... */
  regs.regs_R[MD_REG_PC] = regs.regs_PC;
  printf("sim_main>>regs.regs_PC = %d\n", regs.regs_PC);

  /* check for DLite debugger entry condition */
  if (dlite_check_break(regs.regs_PC, /* !access */0, /* addr */0, 0, 0))
    dlite_main(regs.regs_PC - sizeof(md_inst_t),
	       regs.regs_PC, sim_num_insn, &regs, mem);

	while (TRUE)
	{
      /* maintain $r0 semantics */
#ifndef TARGET_ARM
      regs.regs_R[MD_REG_ZERO] = 0;
#endif
#ifdef TARGET_ALPHA
      regs.regs_F.d[MD_REG_ZERO] = 0.0;
#endif /* TARGET_ALPHA */

      /* keep an instruction count */
      sim_num_insn++;

      /* set default reference address and access mode */
      addr = 0; is_write = FALSE;

		/* determine current processor mode */
		pmode = msk2mode[regs.regs_C.cpsr & 0x1f];
		if (pmode >= 6 || pmode == -1)
			fatal("bogus processor mode");
		/* (4) set default fault - none */
		fault = mem_fault_none;

		/* Service events that are scheduled to occur */
		/* FIXME: Should this happen BEFORE instruction execution? */
		//eventq_service_events(sim_num_insn);

		/* (5) get the next instruction to execute */

		/*MD_FETCH_INST(inst, mem, regs.regs_PC);*/

		_FetchInst(regs.regs_PC, &inst);
		//printf("regs_PC = 0x%x\n", regs.regs_PC);
		//fprintf(fout, "inst = 0x%x	regs.regs_PC = 0x%x		", inst, regs.regs_PC);
		//md_print_insn(inst, regs.regs_PC, fout);
		//fprintf(fout, "\n");
		//md_print_iregs(regs.regs_R, fout);

		/* (6) decode the instruction */
	  MD_SET_OPCODE(op, inst);
      if (op == NA)
	fatal("bogus opcode detected @ 0x%08p", regs.regs_PC);

      setPC = 0;
		setCP15 = -1;
      regs.regs_R[MD_REG_PC] = regs.regs_PC;

      /* execute the instruction */
		
		/* system call handler macro */
#define SYSCALL(INST)	sys_syscall_pesim(&regs, _slow_mem, INST, TRUE)

		/* precise architected memory state accessor macros */
#define READ_BYTE(SRC, FAULT)						\
	((FAULT) = mem_fault_none, _ReadByte((SRC)))
#define READ_HALF(SRC, FAULT)						\
	((FAULT) = mem_fault_none, _ReadHalf((SRC)))
#define READ_WORD(SRC, FAULT)						\
	((FAULT) = mem_fault_none, _ReadWord((SRC)))
#ifdef HOST_HAS_QWORD
#define READ_QWORD(SRC, FAULT)						\
	((FAULT) = mem_fault_none, _ReadQword((SRC)))
#endif /* HOST_HAS_QWORD */	 

#define WRITE_BYTE(SRC, DST, FAULT)					\
	((FAULT) = mem_fault_none, _WriteByte((DST), (SRC)))
#define WRITE_HALF(SRC, DST, FAULT)					\
	((FAULT) = mem_fault_none, _WriteHalf((DST), (SRC)))
#define WRITE_WORD(SRC, DST, FAULT)					\
	((FAULT) = mem_fault_none, _WriteWord((DST), (SRC)))
#ifdef HOST_HAS_QWORD
#define WRITE_QWORD(SRC, DST, FAULT)				\
	((FAULT) = mem_fault_none, _WriteQword((DST), (SRC)))
#endif /* HOST_HAS_QWORD */

      switch (op)
	{
#define DEFINST(OP,MSK,NAME,OPFORM,RES,FLAGS,O1,O2,O3,I1,I2,I3,I4)	\
	case OP:							\
          SYMCAT(OP,_IMPL);						\
          break;
	
#define DEFLINK(OP,MSK,NAME,MASK,SHIFT)					\
        case OP:							\
          panic("attempted to execute a linking opcode");
		
#define CONNECT(OP)

#define DECLARE_FAULT(FAULT)						\
	  { fault = (FAULT); break; }
		
#include "machine.def"
	default:
	  panic("attempted to execute a bogus opcode");
        }
		if (fault != mem_fault_none)
	fatal("fault (%d) detected @ 0x%08p", fault, regs.regs_PC);

      if (setPC != 0/* regs.regs_R[MD_REG_PC] != regs.regs_PC */)
	regs.regs_NPC = regs.regs_R[MD_REG_PC];

      if (verbose && sim_num_insn >= trigger_inst)
	{
	  myfprintf(stderr, "%10n [xor: 0x%08x] @ 0x%08p: ",
		    sim_num_insn, md_xor_regs(&regs), regs.regs_PC);
	  md_print_insn(inst, regs.regs_PC, stderr);
	  fprintf(stderr, "\n");
	  //	  md_print_iregs(regs.regs_R, stderr);
	  //	  md_print_fpregs(regs.regs_F, stderr);
	  //	  md_print_cregs(regs.regs_C, stderr);
	  /* fflush(stderr); */
	}

      if (MD_OP_FLAGS(op) & F_MEM)
	{
	  sim_num_refs++;
	  if (MD_OP_FLAGS(op) & F_STORE)
	    is_write = TRUE;
	}

      /* check for DLite debugger entry condition */
      if (dlite_check_break(regs.regs_NPC,
			    is_write ? ACCESS_WRITE : ACCESS_READ,
			    addr, sim_num_insn, sim_num_insn))
	dlite_main(regs.regs_PC, regs.regs_NPC, sim_num_insn, &regs, mem);

      /* go to the next instruction */
      regs.regs_PC = regs.regs_NPC;
      regs.regs_NPC += sizeof(md_inst_t);

		/* Check for interrupts. If occurred, issue appropriate faults */
		/* (0) check the irq*/
		if (irq_state)
		{
			printf("Core changed mode to IRQ\n");
			//_IrqHandler();
			SET_PSR_MODE(IRQ, regs.regs_PC, regs.regs_NPC);
			regs.regs_NPC = regs.regs_PC + sizeof(md_inst_t);
			trapPC = TRUE;
			irq_state= 0;
		}
		if (ITC_INT_CHK(IController))
		{
			if(!(PSR_FIQ) & (ITC_INT_CHK(IController) == 1) )
			{
				printf("switch (op) 4.1\n");
				if (irq_debug)
					info("FIQ interrupt declared...(icnt:%n,PC:0x%p)",
						sim_num_insn, regs.regs_PC);
				//flt_declare(FAULT_GROUP, md_interrupt_FIQ,
				//	"FIQ Intr registered @ Inst [%llu] : PC 0x0%08p", 
				//	sim_num_insn, regs.regs_PC);
				SET_PSR_MODE(FIQ, regs.regs_PC, regs.regs_NPC);
				regs.regs_NPC = regs.regs_PC + sizeof(md_inst_t);
				trapPC = TRUE;
			}

			if(!(PSR_IRQ) & (ITC_INT_CHK(IController) == -1))
			{
				printf("switch (op) 4.2\n");
				if (irq_debug)
					info("IRQ interrupt declared...(icnt:%n,PC:0x%p)",
				sim_num_insn, regs.regs_PC);
				//flt_declare(FAULT_GROUP, md_interrupt_IRQ,
				//	"IRQ Intr registered @ Inst [%llu] : PC 0x0%08p", 
				//	sim_num_insn, regs.regs_PC);
				SET_PSR_MODE(IRQ, regs.regs_PC, regs.regs_NPC);
				regs.regs_NPC = regs.regs_PC + sizeof(md_inst_t);
				trapPC = TRUE;
			}
		}

		/* finish early? */
		if (max_insts && sim_num_insn >= max_insts)
			return;
		//wait();
	}
}
