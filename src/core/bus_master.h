#ifndef ME_BUS_MASTER_H
#define ME_BUS_MASTER_H

#include "frame_app.h"
#include "bus_types.h"
#include "bus_non_blocking_if.h"

#define TRACE_BUS_MASTER_INFO 1
#undef TRACE_BUS_MASTER_INFO

#undef TRACE_INFO
#ifdef TRACE_BUS_MASTER_INFO
#define TRACE_INFO if(1)
#else
#define TRACE_INFO if(0)
#endif

class Bus_master : public sc_module
{
public:
	// ports
	sc_in_clk clock;
	sc_port<Bus_non_blocking_if> bus_port;
	
	SC_HAS_PROCESS(Bus_master);
	
	// constructor
	Bus_master(sc_module_name _name
		, unsigned int unique_priority
		, unsigned int start_address
		, bool lock
		, int timeout)
		: sc_module(_name)
		, _unique_priority(unique_priority)
		, _start_address(start_address)
		, _lock(lock)
		, _timeout(timeout)
	{
		//init the signal
		cout << "Init the Bus_master:" << endl
			 << "	unique_priority     =   " << _unique_priority << endl
			 << "	start_address       =   " << _start_address << endl
			 << "	lock                =   " << _lock << endl
			 << "	timeout             =   " << _timeout << endl;
		// process declaration
		//SC_THREAD(main_action);
		//sensitive << clock.pos();		
	}
	
	// process
	void main_action();
	
private:
	unsigned int _unique_priority;
	unsigned int _start_address;
	bool _lock;
	int _timeout;
public:
	//signal for trace
	sc_uint<32> raddr;
	sc_uint<32> rdata;	
	sc_uint<32> waddr;
	sc_uint<32> wdata;	
}; // end class simple_bus_master_non_blocking

#endif

