#ifndef ME_TIMER_H
#define ME_TIMER_H

#include "frame_app.h"

class Timer : public sc_module
{
public:
	sc_out<bool> irq;
	sc_in_clk clk;

	void MainAction();

	SC_HAS_PROCESS(Timer);

	Timer(sc_module_name name) : sc_module(name)
	{
		SC_THREAD(MainAction);
		sensitive << clk.pos();
	}
};

#endif
