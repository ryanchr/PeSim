#include "bus_master.h"

void Bus_master::main_action()
{
	Uint32 mydata;
	int cnt = 0;
	unsigned int addr = _start_address;
	
	wait(); // ... for the next rising clock edge
	while (true)
    {
		bus_port->Read(_unique_priority, &mydata, addr, _lock);
		TRACE_INFO{
			raddr = addr;
			rdata = (Uint32)mydata;}
		while ((bus_port->get_status(_unique_priority) != BUS_OK) &&
			(bus_port->get_status(_unique_priority) != BUS_ERROR))
			wait();
		if (bus_port->get_status(_unique_priority) == BUS_ERROR)
			Tools::print2file(stdout, "%g %s : ERROR cannot read from %x\n",
			sc_time_stamp().to_double(), name(), addr);
		
		mydata += cnt;
		cnt++;
		/*
		bus_port->write(m_unique_priority, &mydata, addr, m_lock);
		TRACE_INFO{
			waddr = addr;
			wdata = (Uint32)mydata;}		
		while ((bus_port->get_status(m_unique_priority) != BUS_OK) &&
			(bus_port->get_status(m_unique_priority) != BUS_ERROR))
			wait();
		if (bus_port->get_status(m_unique_priority) == BUS_ERROR)
			tr_fprintf(stdout, "%g %s : ERROR cannot write to %x\n",
			sc_time_stamp().to_double(), name(), addr);
		
		wait(m_timeout, SC_NS);
		wait(); // ... for the next rising clock edge
		*/
		addr+=4; // next word (byte addressing)
		if (addr > (_start_address+0x80)) {
			addr = _start_address; cnt = 0;
		}
    }
}

