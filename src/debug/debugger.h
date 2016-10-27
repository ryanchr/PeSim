/*
*  debugger.h
*
*  Console debugger Class definition
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-12-7 22:31:01 Created.
*
*  Description: The definition of the debugger for the simulator. 
*
*/

#ifndef __FACSIM_DEBUGGER_H__
#define __FACSIM_DEBUGGER_H__
#include "frame_app.h"
#include "topsystem.h"
#include "token.h"
#include "dbg_types.h"
#include <iostream>
#include <string>
#include <deque>
#include <map>
#include <termios.h>
#include <signal.h>
#include <setjmp.h>
using namespace std;
extern jmp_buf g_core_exit;
//=============================================================================
// ConsoleDebugger
//=============================================================================
class ConsoleDebugger
{
public:
	ConsoleDebugger(Topsys *top_system);
	bool CheckSigint();
	virtual void Run();

	Topsys *top_system;
	string macro_file;

private:
	void _InitStrcidMap();
	void _InitHandlerArray();
	//////////////////////////////////////////////////
	// CATEGORY : Execution Control
	int _Run				( Tokenizer* t );
	int _Step				( Tokenizer* t );
	int _Quit				( Tokenizer* t );
	int _Read				( Tokenizer* t );

	//////////////////////////////////////////////////
	// CATEGORY : help
	int _Help				( Tokenizer* t );

	bool _ProcessCommand( istream& is );
	void _PrintHelp( ostream& o );
	void _PrintHelp( ostream& o, COMMANDS cmd);
	void _PrintState();
	string _ReadCommand( );

	bool _flag_run_first;

protected:
	typedef int (ConsoleDebugger::*CommandHandlerFunc)(Tokenizer*);
	typedef map<string, enum COMMANDS> StrCidMap;

	StrCidMap			_str_cid_map;
	CommandHandlerFunc	_handler_func[COMMAND_MAX];

	deque<string>	_line_queue;

};

#endif

