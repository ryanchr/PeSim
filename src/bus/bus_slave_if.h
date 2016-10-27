#ifndef ME_BUS_SLAVE_IF_H
#define ME_BUS_SLAVE_IF_H
#include "frame_app.h"
#include "bus_types.h"
#include "bus_direct_if.h"


class Bus_slave_if
: public Bus_direct_if
{
public:
	// Slave interface
	virtual bus_status Read(Uint32 addr, Uint32 *value) = 0;
	virtual bus_status Write(Uint32 addr, Uint32 *value) = 0;
	
	virtual unsigned int start_address() const = 0;
	virtual unsigned int end_address() const = 0;
	
}; // end class simple_bus_slave_if

#endif
