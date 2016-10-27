/*
*  bus.h
*
*  Bus module definition
*
*  Copyright (C) 2009 Ren Chen and Wang Huan
*
*  2009-11-30 15:44:14 Created.
*
*  Description: The Simple bus is modified from SystemC's example. 
*
*/
#include "frame_app.h"
#include "bus.h"

void Bus::end_of_elaboration()
{
	// perform a static check for overlapping memory areas of the slaves
	bool no_overlap;
	for (int i = 1; i < slave_port.size(); ++i) 
	{
		Bus_slave_if *slave1 = slave_port[i];
		for (int j = 0; j < i; ++j) 
		{
			Bus_slave_if *slave2 = slave_port[j]; 
			no_overlap = ( slave1->end_address() < slave2->start_address() ) ||
				( slave1->start_address() > slave2->end_address() );
			if ( !no_overlap ) 
			{
				//error, address is overlapped
				Tools::print2file(stdout,"Error: overlapping address spaces of 2 slaves : \n");
				Tools::print2file(stdout,"slave %i : %0X..%0X\n",i,slave1->start_address(),slave1->end_address()); 
				Tools::print2file(stdout,"slave %i : %0X..%0X\n",j,slave2->start_address(),slave2->end_address());
				exit(0);
			}
		}
	}
}

//----------------------------------------------------------------------------
//-- process
//----------------------------------------------------------------------------

void Bus::main_action()
{
	// m_current_request is cleared after the slave is done with a
	// single data transfer. Burst requests require the arbiter to
	// select the request again.
	
	if (!m_current_request)
		m_current_request = get_next_request();
	else
		// monitor slave wait states
		if (m_verbose)
			Tools::print2file(stdout, "%g SLV [%d]\n", sc_time_stamp().to_double(),
			m_current_request->address);
		if (m_current_request)    //if can be deleted
			handle_request();
		if (!m_current_request)
			clear_locks();
}

//----------------------------------------------------------------------------
//-- direct BUS interface
//----------------------------------------------------------------------------

bool Bus::direct_read(int *data, unsigned int address)
{
	if (address%4 != 0 ) {// address not word alligned
		Tools::print2file(stdout, "  BUS ERROR --> address %04X not word alligned\n",address);
		return false; 
	}
	Bus_slave_if *slave = get_slave(address);
	if (!slave) return false;
	return slave->direct_read(data, address);
}

bool Bus::direct_write(int *data, unsigned int address)
{
	if (address%4 != 0 ) {// address not word alligned
		Tools::print2file(stdout, "  BUS ERROR --> address %04X not word alligned\n",address);
		return false; 
	}
	Bus_slave_if *slave = get_slave(address);
	if (!slave) return false;
	return slave->direct_write(data, address);
}

//----------------------------------------------------------------------------
//-- non-blocking BUS interface
//----------------------------------------------------------------------------

void Bus::Read(Uint32 unique_priority
			   , Uint32 *data
			   , Uint32 address
			   , bool lock)
{
	if (m_verbose)
		Tools::print2file(stdout, "%g %s : read(%d) @ %x\n",
	       sc_time_stamp().to_double(), name(), unique_priority, address);
	
	Bus_request *request = get_request(unique_priority);
	// abort when the request is still not finished
	sc_assert((request->status == BUS_OK) ||
		(request->status == BUS_ERROR));
	
	request->do_write           = false; // we are reading
	request->address            = address;
	request->end_address        = address;
	request->data               = data;
	
	if (lock)
		request->lock = (request->lock == BUS_LOCK_SET) ? BUS_LOCK_GRANTED : BUS_LOCK_SET;
	
	request->status = BUS_REQUEST;
	//signals
	TRACE_INFO{
	HADDR = address;
	HREADY = DATA_READY;
	HWRITE = BUS_RD;}
}

void Bus::Write(Uint32 unique_priority
				, Uint32 *data
				, Uint32 address
				, bool lock)
{
	if (m_verbose) 
		Tools::print2file(stdout, "%g %s : write(%d) @ %x\n",
	       sc_time_stamp().to_double(), name(), unique_priority, address);
	
	Bus_request *request = get_request(unique_priority);
	
	// abort when the request is still not finished
	sc_assert((request->status == BUS_OK) ||
		(request->status == BUS_ERROR));
	
	request->do_write           = true; // we are writing
	request->address            = address;
	request->end_address        = address;
	request->data               = data;
	
	if (lock)
		request->lock = (request->lock == BUS_LOCK_SET) ?
BUS_LOCK_GRANTED : BUS_LOCK_SET;
	
	request->status = BUS_REQUEST;
	/* Signals */
	TRACE_INFO{
	HADDR = address;
	HREADY = DATA_READY;
	HWRITE = BUS_WR;}
}

bus_status Bus::get_status(unsigned int unique_priority)
{
	return get_request(unique_priority)->status;
}

//----------------------------------------------------------------------------
//-- blocking BUS interface
//----------------------------------------------------------------------------

bus_status Bus::burst_read(unsigned int unique_priority
						   , Uint32 *data
						   , unsigned int start_address
						   , unsigned int length
						   , bool lock)
{
	if (m_verbose) 
	{
		Tools::print2file(stdout, "%g %s : burst_read(%d) @ %x\n",
			sc_time_stamp().to_double(), name(), unique_priority, 
			start_address);
	}
	
	Bus_request *request = get_request(unique_priority);
	
	request->do_write           = false; // we are reading
	request->address            = start_address;
	request->end_address        = start_address + (length-1)*4;
	request->data               = data;
	
	if (lock)
		request->lock = (request->lock == BUS_LOCK_SET) ? 
BUS_LOCK_GRANTED : BUS_LOCK_SET;
	
	request->status = BUS_REQUEST;
	
	wait(request->transfer_done);
	wait(clock->posedge_event());
	return request->status;
}

bus_status Bus::burst_write(unsigned int unique_priority
							, Uint32 *data
							, unsigned int start_address
							, unsigned int length
							, bool lock)
{
	if (m_verbose) 
		Tools::print2file(stdout, "%g %s : burst_write(%d) @ %x\n",
	       sc_time_stamp().to_double(), name(), unique_priority, 
		   start_address);
	
	Bus_request *request = get_request(unique_priority);
	
	request->do_write           = true; // we are writing
	request->address            = start_address;
	request->end_address        = start_address + (length-1)*4;
	request->data               = data;
	
	if (lock)
		request->lock = (request->lock == BUS_LOCK_SET) ? 
BUS_LOCK_GRANTED : BUS_LOCK_SET;
	
	request->status = BUS_REQUEST;
	
	wait(request->transfer_done);
	wait(clock->posedge_event());
	return request->status;
}

//----------------------------------------------------------------------------
//-- BUS methods:
//
//     handle_request()   : performs atomic bus-to-slave request
//     get_request()      : BUS-interface: gets the request form of given 
//                          priority
//     get_next_request() : returns a valid request out of the list of 
//                          pending requests
//     clear_locks()      : downgrade the lock status of the requests once
//                          the transfer is done
//----------------------------------------------------------------------------

void Bus::handle_request()
{
	if (m_verbose)
		Tools::print2file(stdout, "%g %s Handle Slave(%d)\n",
		sc_time_stamp().to_double(), name(), 
		m_current_request->priority);
	
	HREADY = DATA_BUSY;
	m_current_request->status = BUS_WAIT;
	Bus_slave_if *slave = get_slave(m_current_request->address);
	if ((m_current_request->address)%4 != 0 ) {// address not word alligned
		Tools::print2file(stdout, "  BUS ERROR --> address %04X not word alligned\n",m_current_request->address);
		m_current_request->status = BUS_ERROR;
		m_current_request = (Bus_request *)0;
		return;
	}
	if (!slave) {
		Tools::print2file(stdout, "  BUS ERROR --> no slave for address %04X \n",m_current_request->address);
		m_current_request->status = BUS_ERROR;
		m_current_request = (Bus_request *)0;
		return;
	}
	bus_status slave_status = BUS_OK;
	if (m_current_request->do_write)
	{
		//write
		slave_status = slave->Write(m_current_request->address
			, m_current_request->data);
		HWDATA = *m_current_request->data;
	}
	else
	{
		//read
		slave_status = slave->Read(m_current_request->address
			, m_current_request->data);
	}
	//after read or write, analize the status of the slave
	if (m_verbose)
		Tools::print2file(stdout, "  --> status=(%s)\n", bus_status_str[slave_status]);
	
	switch(slave_status)
    {
    case BUS_ERROR:
		m_current_request->status = BUS_ERROR;
		m_current_request->transfer_done.notify();
		m_current_request = (Bus_request *)0;
		break;
    case BUS_OK:
		TRACE_INFO HREADY = DATA_READY;
		m_current_request->address+=4; //next word (byte addressing)
		m_current_request->data++;
		if (m_current_request->address > m_current_request->end_address)
		{
			// burst-transfer (or single transfer) completed
			m_current_request->status = BUS_OK;
			m_current_request->transfer_done.notify();
			m_current_request = (Bus_request *)0;
		}
		else
		{ // more data to transfer, but the (atomic) slave transfer is done
			m_current_request = (Bus_request *)0;
		}
		break;
    case BUS_WAIT:
		// the slave is still processing: no clearance of the current request
		break;
    default:
		break;
    }
}

Bus_slave_if *Bus::get_slave(unsigned int address)
{
	for (int i = 0; i < slave_port.size(); ++i)
    {
		Bus_slave_if *slave = slave_port[i];
		if ((slave->start_address() <= address) &&
			(address <= slave->end_address()))
			return slave;
    }
	return (Bus_slave_if *)0;
}

Bus_request * Bus::get_request(unsigned int priority)
{
	Bus_request *request = (Bus_request *)0;
	for (int i = 0; i < m_requests.size(); ++i)
    {
		request = m_requests[i];
		if ((request) &&
			(request->priority == priority))
			return request;
    }
	request = new Bus_request;
	request->priority = priority;
	m_requests.push_back(request);
	return request;		
}

Bus_request * Bus::get_next_request()
{
	// the slave is done with its action, m_current_request is
	// empty, so go over the bag of request-forms and compose
	// a set of likely requests. Pass it to the arbiter for the
	// final selection
	bus_request_vec Q;
	for (int i = 0; i < m_requests.size(); ++i)
    {
		Bus_request *request = m_requests[i];
		if ((request->status == BUS_REQUEST) ||
			(request->status == BUS_WAIT))
		{
			if (m_verbose) 
				Tools::print2file(stdout, "%g %s : request (%d) [%s]\n",
				sc_time_stamp().to_double(), name(), 
				request->priority, bus_status_str[request->status]);
			Q.push_back(request);
		}
    }
	if (Q.size() > 0)
		return arbiter_port->arbitrate(Q);
	return (Bus_request *)0;
}

void Bus::clear_locks()
{
	for (int i = 0; i < m_requests.size(); ++i)
		if (m_requests[i]->lock == BUS_LOCK_GRANTED)
			m_requests[i]->lock = BUS_LOCK_SET;
		else
			m_requests[i]->lock = BUS_LOCK_NO;
}
