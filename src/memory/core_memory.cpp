#include "core_memory.h"

extern FILE *fout;
extern FILE *fout2;
Bus_slow_mem::~Bus_slow_mem()
{
}

void Bus_slow_mem::wait_loop()
{
  if (m_wait_count >= 0) m_wait_count--;
}

bool Bus_slow_mem::direct_read(Sint32 *data, unsigned int address)
{
	printf("Bus_slow_mem::direct_read No defined\n");
	exit(0);
  //*data = MEM[(address - m_start_address)/4];
  return true;
}

bool Bus_slow_mem::direct_read_08(Uint8 * data, unsigned int address)
{
	printf("Bus_slow_mem::direct_read_08 No defined\n");
	exit(0);
	Uint32 data32;
	Uint32 addr_align;
	addr_align = address & 0xfffffffc;
	Uint8 *data8;
	//data32 = MEM[(addr_align - m_start_address)/4];
	data8 = (Uint8 *)&data32;
	*data = data8[address - addr_align];
}
bool Bus_slow_mem::direct_write(Sint32 *data, unsigned int address)
{
  //MEM[(address - m_start_address)/4] = *data;
  printf("Bus_slow_mem::direct_write No defined\n");
  exit(0);
  return true;
}

bool Bus_slow_mem::direct_write_08(Uint8 * data, unsigned int address)
{
	printf("Bus_slow_mem::direct_write_08 No defined\n");
	exit(0);
	Uint32 data32;
	Uint32 addr_align;
	addr_align = address & 0xfffffffc;
	Uint8 *data8;
	//data32 = MEM[(addr_align - m_start_address)/4];
	data8 = (Uint8 *)&data32;
	data8[address - addr_align] = *data;
	//MEM[(addr_align - m_start_address)/4] = data32;
}

/* copy a '\0' terminated string to/from simulated memory space, returns
   the number of bytes copied, returns any fault encountered */
bool Bus_slow_mem::mem_wstrcpy(Uint32 addr, char *s)
{
	MemStrcpy(CmdWrite, addr, s);
	/*
  int n = 0;
  char c;
  do {
  	c = *s++;
	
	direct_write_08((Uint8 *)&c, addr);
	n++;
	addr++;
      } while (c);
  /* no faults... */
  return true;
}

bool Bus_slow_mem::mem_rstrcpy(Uint32 addr, char *s)
{
	MemStrcpy(CmdRead, addr, s);
/*
  int n = 0;
  char c;
  do {
	direct_read_08((Uint8 *)&c, addr);
	*s++ = c;
	n++;
	addr++;
      } while (c);
  /* no faults... */
  return true;
}

bool Bus_slow_mem::mem_wbcopy(Uint32 addr, Sint32 * buffer, int size)
{
	printf("Bus_slow_mem::mem_wbcopy is no defined\n");
	exit(0);
	MemAccess(CmdWrite, addr, (Uint32 *)buffer, size);
	/*
	Sint32 *pb;
	pb = buffer;
	int tmp = size/4;
	for (int i = 0; i < tmp; i++)
	{
		direct_write(pb, addr);
		addr = addr + 4;
		pb++;
	}
	*/
	return true;
}

bool Bus_slow_mem::mem_rbcopy(Uint32 addr, Sint32 * buffer, int size)
{
	printf("Bus_slow_mem::mem_rbcopy is no defined\n");
	exit(0);
	MemAccess(CmdRead, addr, (Uint32 *)buffer, size);
	/*
	Sint32 *pb;
	pb = buffer;
	int tmp = size/4;
	for (int i = 0; i < tmp; i++)
	{
		direct_read(pb, addr);
		addr = addr + 4;
		pb++;
	}
	*/
	return true;
}

/* copy NBYTES to/from simulated memory space, returns any faults */
fault_t Bus_slow_mem::MemBcopy(enum MemCmd cmd,		/* Read (from sim mem) or Write */
		Uint32 addr,		/* target address to access */
		void *vp,			/* host memory address to access */
		int nbytes)
{
	Uint8 *p = (Uint8*)vp;
	fault_t fault;

  /* copy NBYTES bytes to/from simulator memory */
	while (nbytes-- > 0)
	{
		fault = MemAccess(cmd, addr++, p++, 1);
		if (fault != mem_fault_none)
		return fault;
	}

	/* no faults... */
	return mem_fault_none;
}
bus_status Bus_slow_mem::Read(Uint32 addr, Uint32 *value)
{
	// accept a new call if m_wait_count < 0)
	if (m_wait_count < 0)
	{
		m_wait_count = m_nr_wait_states;
		return BUS_WAIT;
    }
	if (m_wait_count == 0)
	{
		MemAccess(CmdRead, addr, value, 4);
		return BUS_OK;
	}
	return BUS_WAIT;
}

bus_status Bus_slow_mem::Write(Uint32 addr, Uint32 *value)
{
  // accept a new call if m_wait_count < 0)
	if (m_wait_count < 0)
	{
		m_wait_count = m_nr_wait_states;
		return BUS_WAIT;
	}
	if (m_wait_count == 0)
	{
		MemAccess(CmdWrite, addr, value, 4);
		return BUS_OK;
	}
	return BUS_WAIT;
}


unsigned int Bus_slow_mem::start_address() const
{
  return m_start_address;
}

unsigned int Bus_slow_mem::end_address() const
{
  return m_end_address;
}

fault_t Bus_slow_mem::MemAccess(enum MemCmd cmd, Uint32 addr, void *vp, int nbytes)
{
	Uint8 *p = (Uint8*)vp;
	/* check alignments */
	if (/* check size, the size must be an even number*/(nbytes & (nbytes-1)) != 0
		|| /* check max size */nbytes > MD_PAGE_SIZE)
		return mem_fault_access;

	if (/* check natural alignment */(addr & (((nbytes > 4) ? 4:nbytes)-1)) != 0)
		return mem_fault_alignment;
	/* perform the copy */
	{
		if (cmd == CmdRead)
		{
			while (nbytes-- > 0)
			{
				_ReadByte(addr, p);
				p += sizeof(Uint8);
				addr += sizeof(Uint8);
			}
		}
		else
		{
			while (nbytes-- > 0)
			{
				_WriteByte(addr, p);
				p += sizeof(Uint8);
				addr += sizeof(Uint8);
			}
		}
	}
	/* no fault... */
	return mem_fault_none;
}

fault_t Bus_slow_mem::MemStrcpy(enum MemCmd cmd, Uint32 addr, char *s)
{
	int n = 0;
	char c;
	fault_t fault;

	switch (cmd)
    {
    case CmdRead:
		do {/* copy until string terminator ('\0') is encountered */
			fault = MemAccess(CmdRead, addr++, &c, 1);
			if (fault != mem_fault_none)
				return fault;
			*s++ = c;
			n++;
			} while (c);
	  break;

    case CmdWrite:
		do {/* copy until string terminator ('\0') is encountered */
			c = *s++;
			fault = MemAccess(CmdWrite, addr++, &c, 1);
			if (fault != mem_fault_none)
				return fault;
			n++;
			} while (c);
      break;

    default:
      return mem_fault_internal;
  }

  /* no faults... */
  return mem_fault_none;
}
	
void Bus_slow_mem::mem_reg_stats(struct stat_sdb_t *sdb)
{

}

/* print a block of memory, returns any faults encountered */
fault_t Bus_slow_mem::PrintMem(Uint32 addr, int len, FILE *stream)
{
	int data;
	int fmt = -1;
	fault_t fault;

	if (!stream)
		stream = stderr;

	addr &= ~sizeof(Uint32);
	len = (len + (sizeof(Uint32) - 1)) & ~sizeof(Uint32);
	fprintf(stream, "[0x%08x]>>+|", addr);
	while (len-- > 0)
	{
		fault = MemAccess(CmdRead, addr, &data, sizeof(Uint32));
		if (fault != mem_fault_none)
			return fault;
		
		if (++fmt == 8)
		{
			fmt = 0;
			fprintf(stream, "+\n");
			fprintf(stream, "[0x%08x]>>+|", addr);
		}

		fprintf(stream, "0x%08x |", data);
		addr += sizeof(Uint32);
	}

	/* no faults... */
	return mem_fault_none;
}

/* create a flat memory space */
struct MemObj* Bus_slow_mem::_MemCreate()
{
	struct MemObj *mem;

	mem = (struct MemObj*)calloc(1, sizeof(struct MemObj));
	if (!mem)
		printf("out of virtual memory");

	return mem;
}

/* initialize memory system, call before loader.c */
void Bus_slow_mem::_MemInit()
{
	int i;

	/* initialize the first level page table to all empty */
	for (i=0; i < MEM_PTAB_SIZE; i++)
	{
		_mem->ptab[i] = NULL;
	}
	_mem->page_count = 0;
	_mem->ptab_misses = 0;
	_mem->ptab_accesses = 0;
}

/* translate address ADDR in memory space MEM, returns pointer to host page */
Uint8 * Bus_slow_mem::_MemTranslate(Uint32 addr)
{
	struct MemPte *pte, *prev;
	/* got here via a first level miss in the page tables */
	_mem->ptab_misses++;
	_mem->ptab_accesses++;

	/* locate accessed PTE */
	for (prev=NULL, pte=_mem->ptab[MEM_PTAB_SET(addr)]; pte != NULL; prev=pte, pte=pte->next)
	{
		if (pte->tag == MEM_PTAB_TAG(addr))
		{
			/* move this PTE to head of the bucket list */
			if (prev)
			{
				prev->next = pte->next;
				pte->next = _mem->ptab[MEM_PTAB_SET(addr)];
				_mem->ptab[MEM_PTAB_SET(addr)] = pte;
			}
			return pte->page;
		}
	}

	/* no translation found, return NULL */
	return NULL;
}

Uint8 *Bus_slow_mem::_MemPage(Uint32 addr)
{
	Uint8 *page;
	if (_mem->ptab[MEM_PTAB_SET(addr)] 
		&& _mem->ptab[MEM_PTAB_SET(addr)]->tag == MEM_PTAB_TAG(addr))
	{
		_mem->ptab_accesses++;
		page = _mem->ptab[MEM_PTAB_SET(addr)]->page;
	}
	else
	{
		page = _MemTranslate(addr);
	}
	return page;
}


void Bus_slow_mem::_MemNewPage(Uint32 addr)
{
	Uint8 *page;
	struct MemPte *pte;

	page = (Uint8*)calloc(MD_PAGE_SIZE, 1);
	if (!page)
		printf("out of virtual memory\n");

	/* generate a new PTE */
	pte = (MemPte*)calloc(1, sizeof(struct MemPte));
	if (!pte)
		printf("out of virtual memory\n");

	pte->tag = MEM_PTAB_TAG(addr);
	pte->page = page;

	/* insert PTE into inverted hash table */
	pte->next = _mem->ptab[MEM_PTAB_SET(addr)];
	_mem->ptab[MEM_PTAB_SET(addr)] = pte;

	/* one more page allocated */
	_mem->page_count++;
}

void Bus_slow_mem::_ReadByte(Uint32 addr, Uint8 *value)
{
	Uint8 *page;
	page = _MemPage(addr);

	if (page)
	{
		*value = *(Uint8 *)(_MemPage(addr) + MEM_OFFSET(addr));
	}
	else	
	{
		*value = 0;	
	}
}
void Bus_slow_mem::_ReadWord(Uint32 addr, Uint32 *value)
{}

void Bus_slow_mem::_WriteByte(Uint32 addr, Uint8 *value)
{
	Uint8 *page;
	page = _MemPage(addr);
	if (!page)
	{
		_MemNewPage(addr);
	}
	*(Uint8 *)(_MemPage(addr) + MEM_OFFSET(addr)) = *value;
}

void Bus_slow_mem::_WriteWord(Uint32 addr, Uint32 *value)
{}

