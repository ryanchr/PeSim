/*
*  debugger.cpp
*
*  Console debugger Class definition
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-12-7 22:31:19 Created.
*
*  Description: The definition of the debugger for the simulator. 
*
*/

#include <debugger.h>



//The code in this section is too urgly, I have no idear.
jmp_buf g_core_exit;

static bool gctrlc = true;
static Topsys *tmp_sys;
static void SignalHandler( int signo )
{
	/*stop the simulator*/
	//tmp_sys->SimPause();
	gctrlc = false;
	signal(SIGINT, NULL);
	cout << endl << "Simulation time : " << sc_simulation_time() << endl;	
}

ConsoleDebugger::ConsoleDebugger(Topsys *top_system)
	: top_system(top_system)
{
	_flag_run_first = true;
	_InitStrcidMap();
	_InitHandlerArray();

	//Be careful about this pointer!!
	tmp_sys = top_system;
	
	int jmpret = setjmp(g_core_exit);
	if (jmpret)
	{
		/*exit frome the system call*/
		cout << "The program stops at time : " << sc_simulation_time() << endl;

		/*stop the _run()*/
		gctrlc = false;
		_PrintState();
		_ProcessCommand(cin);
	}
}

bool ConsoleDebugger::CheckSigint()
{
	bool ret = gctrlc;
	gctrlc = false;
	return ret;
}

void ConsoleDebugger::_InitStrcidMap()
{
	//////////////////////////////////////////////////
	// CATEGORY : Execution Control
	_str_cid_map["run"] = RUN;
	_str_cid_map["r"] = RUN;

	_str_cid_map["step"] = STEP;
	_str_cid_map["s"] = STEP;

	_str_cid_map["quit"] = QUIT;
	_str_cid_map["q"] = QUIT;

	_str_cid_map["read"] = READ;
	

	//////////////////////////////////////////////////
	// CATEGORY : help
	_str_cid_map["help"] = HELP;
	_str_cid_map["h"] = HELP;

}

void ConsoleDebugger::_InitHandlerArray()
{
	//////////////////////////////////////////////////
	// CATEGORY : Execution Control
	_handler_func[RUN] 		= &ConsoleDebugger::_Run;
	_handler_func[STEP] 	= &ConsoleDebugger::_Step;
	_handler_func[QUIT]		= &ConsoleDebugger::_Quit;
	_handler_func[READ]		= &ConsoleDebugger::_Read;

	//////////////////////////////////////////////////
	// CATEGORY : help
	_handler_func[HELP]		= &ConsoleDebugger::_Help;
}

int ConsoleDebugger::_Run(Tokenizer * t)
{
	/*
	if (_flag_run_first)
	{
		signal( SIGINT, SignalHandler);
		sc_start();
		_flag_run_first = false;
	}
	else
	{
		signal( SIGINT, SignalHandler);
		top_system->SimContinue();
	}
	*/
	string token;
	Uint32 resolution;
	if ( ( token = t->getNextToken() ) != "" )
	{                
		if ( Tools::StringToUint32( token, resolution ) )
		{
			cout << "The input is right: resolution = " << resolution << endl;
		}
		else
		{
			_PrintHelp( cerr, STEP);
		}
	}
	else
	{
		resolution = 100;
	}
	gctrlc = true;
	while(gctrlc)
	{
		sc_start(resolution, SC_NS);
		signal( SIGINT, SignalHandler);
	}

	return 0;
}

int ConsoleDebugger::_Step(Tokenizer * t)
{
	Sint32 result = 0;
	string token;
	if ( ( token = t->getNextToken() ) != "" )
	{                
		Uint32 num_cycles;
		if ( Tools::StringToUint32( token, num_cycles ) )
		{
			cout << "The input is right: num_cycles = " << num_cycles << endl;
			sc_start(num_cycles, SC_NS);
			result = 0;
			
		}
		else
		{
			_PrintHelp( cerr, STEP);
		}
	}
	else
	{
		sc_start(1, SC_NS);
		result = 0;
	}

	return result;
}

int ConsoleDebugger::_Quit(Tokenizer * t)
{
	sc_stop();
	cout << "quit handler function" << endl;
	return 1;
}

int ConsoleDebugger::_Read(Tokenizer * t)
{
	string token;

	if ((token = t->getNextToken()) != "")
	{                
		Uint32 addr;
		Uint32 len = 16;

		if ( Tools::StringToUint32(token, addr))
		{
			if ((token = t->getNextToken()) != "")
				Tools::StringToUint32(token, len);
			
			cout << "The input is right: addr = 0x" << std::hex << addr 
				<< "len	= 0x" << std::hex << len << endl;
			
			top_system->mem_slow->PrintMem(addr, len, stderr);
			return 0;
		}
		else
		{
			_PrintHelp( cerr, READ);
			return 0;
		}
	}
	else
	{
		_PrintHelp( cerr, READ);;
		return 0;
	}
	
}

bool ConsoleDebugger::_ProcessCommand( istream& is )
{
	string 	line;
	char	szBuf[100];

	bool exit_condition = false;
	
	#define EXCEPTION_MEMBREAK 8
	while( ! exit_condition && exit_condition != EXCEPTION_MEMBREAK )
	{
		cerr << "PeSim# ";
		/*for console input*/
		if( is == cin )
		{
			is.getline( szBuf, 100 );
			line = szBuf;

			if( line.empty() )
			{
				/*run previous command once more.*/
				if( _line_queue.size() == 0 )
					continue;

				line = _line_queue.back();

				cerr << line << endl;
			}
			/*insert the command to the command queue*/
			if( _line_queue.size() > 0 && _line_queue.back() != line )
				_line_queue.push_back( line );
			else if ( _line_queue.size() == 0 )
				_line_queue.push_back( line );

			if( _line_queue.size() > 10 )
			{
				_line_queue.pop_front();
			}

		}
		/*for macro file*/
		else
		{

		}
		Tokenizer* t = new Tokenizer( line );
		string token = t->getNextToken();

		StrCidMap::iterator iter = _str_cid_map.find( token );
		if( iter != _str_cid_map.end() )
		{ 
			exit_condition = (this->*_handler_func[ iter->second ])( t );
		}
		else
		{
			cerr << "undefined command sequence : " << token << endl;
		}
		//cout << "## " << top_system->controler->SimCycles() << endl;
		_PrintState();
	}

	return exit_condition;
}

int ConsoleDebugger::_Help( Tokenizer* t )
{
	string token;

	if ( ( token = t->getNextToken() ) == "" ) 
	{
		_PrintHelp( cerr );
	}
	else
	{
		StrCidMap::iterator iter = _str_cid_map.find( token );

		if( iter != _str_cid_map.end() )
		{
			_PrintHelp( cerr, iter->second );
		}
		else
		{
			cerr << "undefined command : " << token;
		}
	}

	return 0;
}
void ConsoleDebugger::_PrintHelp(ostream & o)
{
	o << endl << "List of Commands" << endl << endl;

	o <<
"Simulation Control" << endl << 
"  run           go          quit            step" << endl << endl<<
"Help" << endl <<
"  help" << endl;

}

void ConsoleDebugger::_PrintHelp(ostream & o, COMMANDS cmd)
{
	switch( cmd )
	{
	//////////////////////////////////////////////////
	// CATEGORY : Execution Control
	case RUN:
		o << "run" << endl
		  << "go" << endl
		  << "  Run the reconfigurable model." << endl << endl;
		break;

	case STEP:
		o << "step [<number_of_clock>=1]" << endl
		  << "  Execute a specified number of clocks." << endl
		  << "  <number_of_clocks> : The number of clocks to be simulated." << endl<< endl;
		break;

	case READ:
		o << "read [<address>] [<size>]" << endl
		  << "  Read the content of memory." << endl
		  << "  <address> 	: The address to be access." << endl
		  << "  <size>		: The size to be read" << endl;
		break;

	default:
		o << "undefined command id : " << cmd << endl << endl;
	}
}

void ConsoleDebugger::_PrintState()
{
	cout << "Simulation time : " << sc_simulation_time() << endl;
	top_system->core->PrintState();
}
void ConsoleDebugger::Run()
{
	bool quit = false;

	if( macro_file.size() )
	{
		ifstream fin( macro_file.c_str() );

		quit = _ProcessCommand( fin );

		fin.close();
	}

	if( !quit )
		_ProcessCommand( cin );
}


