#include "timer.h"

void Timer::MainAction()
{
	Uint32 count = 0;

	while (1)
	{
		if (count++ == 50)
		{
			cout << "Timer raised an IRQ\n";
			//irq = 1;
		}
		else
		{
			irq = 0;
		}
		wait();
	}
}