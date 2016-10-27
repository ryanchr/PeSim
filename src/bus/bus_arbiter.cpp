#include "frame_app.h"
#include "bus_arbiter.h"

Bus_request *
Bus_arbiter::arbitrate(const bus_request_vec &requests)
{
	int i;
	// at least one request is here
	Bus_request *best_request = requests[0]; 
	
	if (m_verbose) 
    { // shows the list of pending requests
		Tools::print2file(stdout, "%g %s :", sc_time_stamp().to_double(), name());
		for (i = 0; i < requests.size(); ++i)
		{
			Bus_request *request = requests[i];
			// simple_bus_lock_status encoding
			const char lock_chars[] = { '-', '=', '+' };
			// simple_bus_status encoding
			Tools::print2file(stdout, "\n    R[%d](%c%s@%x)",
				request->priority,
				lock_chars[request->lock],
				bus_status_str[request->status],
				request->address);
		}
    }
	
	// highest priority: status==SIMPLE_BUS_WAIT and lock is set: 
	// locked burst-action
	for (i = 0; i < requests.size(); ++i)
    {
		Bus_request *request = requests[i];
		if ((request->status == BUS_WAIT) &&
			(request->lock == BUS_LOCK_SET))
		{
			// cannot break-in a locked burst
			if (m_verbose)
				Tools::print2file(stdout, " -> R[%d] (rule 1)\n", request->priority);
			return request;
		}
    }
	
	// second priority: lock is set at previous call, 
	// i.e. SIMPLE_BUS_LOCK_GRANTED
	for (i = 0; i < requests.size(); ++i)
		if (requests[i]->lock == BUS_LOCK_GRANTED)
		{
			if (m_verbose)
				Tools::print2file(stdout, " -> R[%d] (rule 2)\n", requests[i]->priority);
			return requests[i];
		}
		
		// third priority: priority
		for (i = 1; i < requests.size(); ++i)
		{
			sc_assert(requests[i]->priority != best_request->priority);
			if (requests[i]->priority < best_request->priority)
				best_request = requests[i];
		}
		
		if (best_request->lock != BUS_LOCK_NO)
			best_request->lock = BUS_LOCK_GRANTED;
		
		if (m_verbose) 
			Tools::print2file(stdout, " -> R[%d] (rule 3)\n", best_request->priority);
		
		return best_request;
}
