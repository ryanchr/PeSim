#include "pe_cfgmem.h"

 PE_cfg_mem::~PE_cfg_mem ()
 {
	if(cfgmem) {delete cfgmem;cfgmem=0;}
}

void PE_cfg_mem::cfgwait_loop()
{
    while(1)
    {
      //printf("------------------hello------------------------");
     // if (m_wait_count >= 0) m_wait_count--;
      wait();
    }
}


bus_status PE_cfg_mem::Read(Uint32 addr, Uint32 *value)
{
	// accept a new call if m_wait_count < 0)
	if (m_wait_count < 0)
	{
		m_wait_count = m_nr_wait_states;
		return BUS_WAIT;
    }
	if (m_wait_count == 0)
	{
		//MemAccess(cfgCmdRead,addr,value,4);
		// cfgmem += (addr-m_start_address)*sizeof(Uint32);
		 *value = cfgmem[addr-m_start_address];     //FIXME
		 return BUS_OK;
	}
	return BUS_WAIT;
}

bus_status PE_cfg_mem::Write(Uint32 addr, Uint32 *value)
{
  // accept a new call if m_wait_count < 0)
	if (m_wait_count < 0)
	{
		m_wait_count = m_nr_wait_states;
		return BUS_WAIT;
	}
	if (m_wait_count == 0)
	{
	      // cfgmem +=  (addr-m_start_address)*sizeof(Uint32);
	      cfgmem[addr-m_start_address] = *value;    //FIXME,It need better description
		return BUS_OK;
	}
	return BUS_WAIT;
}


unsigned int PE_cfg_mem::start_address() const
{
  return m_start_address;
}

unsigned int PE_cfg_mem::end_address() const
{
  return m_end_address;
}

bool PE_cfg_mem::direct_read(Sint32 *data, unsigned int address)
{
	printf("PE_cfg_mem::direct_read No defined\n");
	exit(0);
  //*data = MEM[(address - m_start_address)/4];
  return true;
}


bool PE_cfg_mem::direct_write(Sint32 *data, unsigned int address)
{
  //MEM[(address - m_start_address)/4] = *data;
  printf("PE_cfg_mem::direct_write No defined\n");
  exit(0);
  return true;
}


void PE_cfg_mem::cfgmem_init()
{
    int i;
    for(i=0;i<(m_end_address-m_start_address+1);i++)
        cfgmem[i]=NULL;
}


