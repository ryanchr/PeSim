#ifndef ME_BUS_REQUEST_H
#define ME_BUS_REQUEST_H

enum bus_lock_status 
{ 
	BUS_LOCK_NO = 0
		, BUS_LOCK_SET
		, BUS_LOCK_GRANTED 
};

class Bus_request
{
public:
	// parameters
	unsigned int priority;
	
	// request parameters
	bool do_write;
	unsigned int address;
	unsigned int end_address;
	Uint32 *data;
	bus_lock_status lock;
	
	// request status
	sc_event transfer_done;
	bus_status status;
	
	// default constructor
	Bus_request();
};

inline Bus_request::Bus_request()
: priority(0)
, do_write(false)
, address(0)
, end_address(0)
, data((Uint32 *)0)
, lock(BUS_LOCK_NO)
, status(BUS_OK)
{}

#endif
