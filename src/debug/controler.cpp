#include "controler.h"

void Controler::SimPause()
{
	cout << "Controler::SimPause()" << endl;
	_flag_pause = true;
}

void Controler::SimContinue()
{
	_flag_pause = false;
}

Uint64 Controler::SimCycles()
{
	return _counter;
}
void Controler::MainIdle()
{
	_counter++;
	bool flag = true;
	while (_flag_pause)
	{
		if (flag)
		{
			flag = false;
			cout << "ctr simulatio paused" << endl;
		}
	}
}