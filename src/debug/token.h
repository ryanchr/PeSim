/*
*  token.h
*
*  definition
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-12-7 22:33:06 Created.
*
*  Description: . 
*
*/

#ifndef __FACSIM_TOKEN_H__
#define __FACSIM_TOKEN_H__

#include <string>
#include <iostream>

using namespace std;

/////**************************************************************************
//=============================================================================
// Tokenizer
//==============================================================================
class Tokenizer 
{
 public:
        Tokenizer( string& line );
	~Tokenizer() {};

	string  getNextToken();
	string  token() const;

 private:
	string  _line;
	int     _pos;
	string	_token; // current token
};


#endif
