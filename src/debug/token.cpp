#include "token.h"

/////**************************************************************************
//=============================================================================
// Tokenizer
//=============================================================================
/*
*  token.cpp
*
*  definition
*
*  Copyright (C) 2009  Ren Chen and Wang Huan
*
*  2009-12-7 22:33:26 Created.
*
*  Description: . 
*
*/
Tokenizer::Tokenizer( string& line )
{
	_line = line;

	_pos  = 0;
}

string Tokenizer::getNextToken()
{
	unsigned int i, begin, end;

	for ( i = _pos; i < _line.size() ; i++ )
	{ 
		if ( ( _line[ i ] != ' ' ) && 
			 ( _line[ i ] != '\t' ) && 
			 ( _line[ i ] != '\n' ) )
		{
			break;
		} 
	}

	begin = i;

	for ( i = begin; i < _line.size() ; i++ )
	{ 
		if ( ( _line[ i ] == ' ' ) || 
			 ( _line[ i ] == '\t' ) || 
			 ( _line[ i ] == '\n' ) )
		{
			break;
		} 
	}

	end = i;

	if ( begin < end )
	{
		_pos = end;

		_token = _line.substr( begin, end - begin );
	} 
	else 
	{
		_token = "";
	}

	return _token;
}

string Tokenizer::token() const
{
	return _token;
}
