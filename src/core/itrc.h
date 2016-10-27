/*
 * itc.h -- interfaces for interrupt controller
 *
 * INTERRUPT CONTROLLER OPERATION
 * 
 * This module implements the interrupt controller for the SA1110 
 * microprocessor.  It contains state for all architected interrupt 
 * controller registers, as well as additional state to ensure that no two 
 * device interrupts are mapped to the same bit.  Callback and ODB
 * registration functions are the same as in other memory-mapped devices;
 * note that the callback function is the access function for all 
 * interrupt controller registers.  In order to configure the simulator 
 * for interrupt controller use include the command line option "-dev:itc".
 *
 * Devices wishing to cause FIQ or IRQ interrupts via the interrupt
 * controller must register with the interrupt controller using the 
 * function itc_reg_dev.  When registering, the device must register all
 * of its interrupts at once; it does so by passing an array of int_desc_t
 * structures while also indicating the number of interrupts in the array.
 * itc_reg_dev returns an integer which uniquely identifies each device;
 * the device must pass this identifier as an argument to the interrupt set
 * macro ITC_INT_SET, along with a pointer to the interrupt controller 
 * itself and the bit corresponding to the desired interrupt.  The 
 * interrupt clear macro requires no such argument as interrupts may be 
 * cleared by the system.  
 *
 * To check if an interrupt occurs, use the macro ITC_INT_CHK, which again
 * requires a pointer to the interrupt controller as well as an argument
 * into which the return value can be passed.  A non-zero return value
 * indicates an interrupt (-1 for IRQ, 1 for FIQ); a zero return value
 * indicates no interrupt.
 * 
 */
#ifndef ITC_H
#define ITC_H

#include <stdio.h>
#include <stdlib.h>

//#include "core_misc.h"
#include "core_memory.h"
#include "memory.h"
/*
 * Descriptive structure for each registered interrupt
 */
struct int_desc_t {
  char *name;           /* Descriptive name of interrupt */
  int bit;              /* Describes which bit of ICPR, ICFP, ICIP 
			   interrupt affects */
};

/* ITC state */
struct ITC_state {
  Uint32 ICIP;                    /* ITC IRQ pending reg. */
  Uint32 ICMR;                    /* ITC mask reg. */
  Uint32 ICLR;                    /* ITC level reg. */
  Uint32 ICCR;                    /* ITC control reg. */
  Uint32 ICFP;                    /* ITC FIQ pending reg. */
  Uint32 ICPR;                    /* ITC pending reg. */

  char *dev_list[32];              /* Descriptive names for devices 
				      associated with each given interrupt */
  int dev_id[32];                  /* ID #s for each device; used to check
				      that correct device causes interrupt */
  char *int_list[32];              /* Descriptive names for each given
				      interrupt */
  Uint32 dev_mask;                /* Each bit of mask:
				      = 0 if no registered device modifies it
				      = 1 if a registered device modifies it
			           */
};

/* Updates state of ITC by flipping specified bit; called in interrupt 
   set/clear macros */
void ITC_UPDATE(struct ITC_state *itc, int bit);

/* Interrupt set/clear macros */
void ITC_INT_SET(struct ITC_state *ITC, int ID, unsigned short BIT);

Uint64 test_func(int bob);

#define ITC_INT_CLR(ITC, BIT)						\
  ((ITC->ICPR & (1 << BIT))						\
   ? ITC_UPDATE(ITC,BIT)						\
   : warn("Interrupt already cleared"))

/* 
 * Macro which checks if interrupt has occurred and places result in INT
 *     = 0 if no interrupt
 *     = 1 if FIQ interrupt
 *    = -1 if IRQ interupt                                           
 */
#define ITC_INT_CHK(ITC)						\
  ((ITC->ICPR & ITC->ICMR) ? ((ITC->ICFP) ? (1) : (-1)) : (0))


/* ITC callback function */
Uint64 itc_access(struct mem_t *mem,
		   enum mem_cmd cmd,
		   md_addr_t addr,
		   enum md_fault_type *itc_fault,
		   void *p,
		   int nbytes);

/* ODB reg function */
struct ITC_state *ITC_init();


/* ITC reg function--allows devices to register with ITC */
/* Returns device ID; used in set macro to ensure correct device is
   causing interrupt */
int itc_reg_dev(char *name,                     /* device name */
		int num_itrs,                   /* number of associated 
						   interrupts */
		struct int_desc_t *int_list);   /* associated 
						   interrupts */

void itc_device_info(FILE *stream);

#endif /* ITC_H */


