/*
 * itc.c -- routines for interrupt controller
 *
 * 7/27/2001 geigerm
 *
 */

#include <string.h>

#include "misc.h"
#include "memory.h"
#include "itrc.h"
#include "core_memory.h"

struct ITC_state *current_ITC;
int ids;

/* Updates state of ITC by flipping specified bit; called in interrupt 
   set/clear macros */
void
ITC_UPDATE(struct ITC_state *itc, int bit)
{
  word_t masked_ints;

  itc->ICPR = itc->ICPR ^ (1 << bit);

  if (!(itc->ICCR & 1))
    warn("Interrupt and DIM is clear...");

  if ((itc->ICCR & 1) == 0)             /* DIM bit cleared */
    masked_ints = itc->ICPR;
  else                                  /* DIM bit set */
    masked_ints = itc->ICPR & itc->ICMR;

  itc->ICFP = masked_ints & itc->ICLR;
  itc->ICIP = masked_ints & ~itc->ICLR;
}

/* Interrupt set/clear macros */
void
ITC_INT_SET(struct ITC_state *ITC, int ID, unsigned short BIT)
{
  if (ID == ITC->dev_id[BIT]) 
    {
      if (ITC->ICPR & (1 << BIT))                                  
	fatal("Interrupt already set, ICPR=0x%08x", ITC->ICPR);
      else
	ITC_UPDATE(ITC,BIT);
    }
  else
    fatal("Wrong device attempting to set interrupt");
  return;
}

/*
 * ITC callback function
 *
 * Note that some regs (ICIP, ICPR, ICFP) are read-only and therefore a write
 * has no effect; others (ICMR, ICLR, ICCR) are read/write 
 */
Uint64
itc_access(enum MemCmd cmd,
	   Uint32 addr,
	   enum mem_fault_type *itc_fault,
	   void *p,
	   int nbytes)
{
  Uint64 itc_reg_val;

  if (debugging)
    info("ITC `%s' access to addr %p, %d bytes",
	 cmd == Write ? "write" : "read", addr, nbytes);

  if (!current_ITC)
    fatal("Attempted to access ITC when it does not exist!");
  if ((nbytes > 4) || (nbytes < 0))
    fatal("Invalid copy size [ITC]");

  /* Check address and act accordingly */
  if (cmd == Write)
    {
      if (!p || (nbytes <= 0))
	fatal("Invalid write data [ITC]");

      itc_reg_val = *(word_t *)p;

      switch (addr) {
    
	/* Read-only registers */
      case 0x90050000:        /* ICIP */
      case 0x90050010:        /* ICFP */
      case 0x90050020:        /* ICPR */
	break;
    
      case 0x90050004:        /* ICMR */
	current_ITC->ICMR = itc_reg_val;
	break;

      case 0x90050008:        /* ICLR */
	current_ITC->ICLR = itc_reg_val;
	break;

      case 0x9005000c:        /* ICCR */
	current_ITC->ICCR = itc_reg_val;
	break;

      default:
	fatal("Invalid address %x in ITC write", addr);
      }
    }
  else
    {
      switch (addr) {

      case 0x90050000:        /* ICIP */
	itc_reg_val = current_ITC->ICIP;
	break;

      case 0x90050004:        /* ICMR */
	itc_reg_val = current_ITC->ICMR;
	break;

      case 0x90050008:        /* ICLR */
	itc_reg_val = current_ITC->ICLR;
	break;

      case 0x9005000c:        /* ICCR */
	itc_reg_val = current_ITC->ICCR;
	break;

      case 0x90050010:        /* ICFP */
	itc_reg_val = current_ITC->ICFP;
	break;

      case 0x90050020:        /* ICPR */
	itc_reg_val = current_ITC->ICPR;
	break;

      default:
	fatal("Invalid address %x in ITC read", addr);
      }
      if (p)
	*(word_t *)p = itc_reg_val & (0xffffffff >> (4 - nbytes));
    }
  return itc_reg_val;
}

/* ODB reg function */
struct ITC_state *
ITC_init()
{
  int i;

  /* Allocate ITC state */
  if(current_ITC)
    fatal("[ITC] mult intantiations of intr controller not supported");

  current_ITC = (struct ITC_state *)calloc(1, sizeof(struct ITC_state));
  if (!current_ITC)
    fatal("Could not allocate space for ITC state");

  for (i = 0; i < 32; i++)
    {
      current_ITC->dev_list[i] = NULL;
      current_ITC->int_list[i] = NULL;
      current_ITC->dev_mask = 0;
    }

  current_ITC->ICIP = 0;
  current_ITC->ICMR = 0;
  current_ITC->ICLR = 0;
  current_ITC->ICCR = 0;
  current_ITC->ICFP = 0;
  current_ITC->ICPR = 0;

  ids = 0;

  //mem_reg_dev(mem_space, "itc_access", itc_access, 0x90050000, 0x23, NULL);
  
  return current_ITC;
}

/* ITC reg function */
int
itc_reg_dev(char *name, 
	    int num_itrs,
	    struct int_desc_t *int_list)
{
  int i, bit;
  word_t tmp_mask;

  /* Sanity checks */
  if (!current_ITC)
    fatal("Attempted ITC device registration without ITC");
  if (!name || !(*name))
    fatal("Attempted ITC device registration without name");

  for (i = 0; i < 32; i++)
    {
      if (current_ITC->dev_mask & (1 << i))
	{
	  if (!strcmp(name, current_ITC->dev_list[i]))
	    fatal("Device %s registered twice with ITC", name);
	}
    }

  for (i = 0; i < num_itrs; i++)
    {
      bit = int_list[i].bit;
      tmp_mask = 1 << bit;
      if (current_ITC->dev_mask & tmp_mask)
	fatal("Multiple device interrupts mapped to same bit");  
      current_ITC->dev_mask = current_ITC->dev_mask | tmp_mask;
      current_ITC->dev_list[bit] = mystrdup(name);
      current_ITC->int_list[bit] = mystrdup(int_list[i].name);
      current_ITC->dev_id[bit] = ids;
    }
  return ids++;  /* Give device next available ID and increment */
}

void
itc_device_info(FILE *stream)
{
  int i;

  myfprintf(stream, "*ITC* device interrupt map *ITC*\n");
  for (i=0; i < 32; i++)
    {
      if (current_ITC->dev_mask & (1 << i))
	{
	  /* active */
	  myfprintf(stream, "  %2d: dev(%s),id(%d),int(%s)\n",
		    i, current_ITC->dev_list[i],
		    current_ITC->dev_id[i],
		    current_ITC->int_list[i]);
	}
      else
	myfprintf(stream, "  %2d: <unused>\n", i);
    }
}


