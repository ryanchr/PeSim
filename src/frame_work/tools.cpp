#include <stdarg.h>
#include <errno.h>
#include "Tools.h"

int Tools::print2file(FILE *fp, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	int ret = 0;
	do {
		errno = 0;
		ret = vfprintf(fp, fmt, ap);
	} while (errno == EINTR);
	return ret;
}



ostream& Tools::printHex( ostream& o, Uint32 v )
{
	o << "0x"; 

	o << hex << v << dec;

	return o;
}

ostream& Tools::printHex( ostream& o, Uint32 v, int w )
{
	o << "0x"; 

	o.fill( '0' );

	o.width( w );

	o.flags( ios::right );

	o << hex << v << dec;

	o.flags( ios::left );

	o.fill( ' ' );

	return o;
}

ostream& Tools::printHex04( ostream& o, Uint32 v ) 
{
	o << "0x"; 

	o.fill( '0' );

	o.width( 1 );

	o << hex << v << dec;

	o.fill( ' ' );

	return o;
}

ostream& Tools::printHex08( ostream& o, Uint32 v )
{
	o << "0x"; 

	o.fill( '0' );

	o.width( 2 );

	o.flags( ios::right );

	o << hex << v << dec;

	o.flags( ios::left );

	o.fill( ' ' );

	return o;
}

ostream& Tools::printHex12( ostream& o, Uint32 v )
{
	o << "0x"; 

	o.fill( '0' );

	o.width( 3 );

	o.flags( ios::right );

	o << hex << v << dec;

	o.flags( ios::left );

	o.fill( ' ' );

	return o;
}

ostream& Tools::printHex16( ostream& o, Uint32 v )
{
	o << "0x"; 

	o.fill( '0' );

	o.width( 4 );

	o.flags( ios::right );

	o << hex << v << dec;

	o.flags( ios::left );

	o.fill( ' ' );

	return o;
}

ostream& Tools::printHex24( ostream& o, Uint32 v ) 
{
	o << "0x"; 

	o.fill( '0' );

	o.width( 6 );

	o.flags( ios::right );

	o << hex << v << dec;

	o.flags( ios::left );

	o.fill( ' ' );

	return o;
}

ostream& Tools::printHex32( ostream& o, Uint32 v )
{
	o << "0x";

	o.fill( '0' );

	o.width( 8 );

	o.flags( ios::right );

	o << hex << v << dec;

	o.flags( ios::left );

	o.fill( ' ' );

	return o;
}

ostream& Tools::printDec( ostream& o, const Uint32 v, int w )
{
	o.fill( ' ' );

	o.width( w );

	o.flags( ios::right );

	o << v;

	o.flags( ios::left );

	return o;
}

ostream& Tools::printDec( ostream& o, const Sint32 v, int w )
{
	o.fill( ' ' );

	o.width( w );

	o.flags( ios::right );

	o << v;

	o.flags( ios::left );

	return o;
}

ostream& Tools::printDec( ostream& o, const Sint64 v, int w )
{
	o.fill( ' ' );

	o.width( w );

	o.flags( ios::right );

	o << v;

	o.flags( ios::left );

	return o;
}

ostream& Tools::printBin32( ostream& o, Uint32 v )
{
        Uint32 m = 0x80000000;

	o << "0b";

        for ( int i = 0; i < 32; i++ )
	{
	        if ( v & m ) 
		{
		        o << "1";
		}
		else
		{
		        o << "0";
		}

		m = m >> 1;
	}

	return o;
}

string Tools::Uint32ToString( Uint32 v )
{
	string s;

	Uint32ToString( v, s );

	return s;
}

void Tools::Uint32ToString( Uint32 v, string& s )
{
	int		temp;
	bool	first = false;

	Uint32 divider = 1000000000;

	while( divider )
	{
		temp = v / divider;

		if( !first && temp != 0 )
		{
			first = true;
		}

		if( first )
		{
			s.append( 1, temp + '0' );
		}

		v %= divider;

		divider /= 10;
	}

	if( !first )
		s = "0";
}

bool Tools::StringToUint32( string& s, Uint32& v )
{
	if ( s.size() > 0 )
	{
		if ( s[ 0 ] == '0' )
		{
			if ( ( s[ 1 ] == 'x' ) || ( s[ 1 ] == 'X' ) )
			{
				for ( Uint32 i = 2; i < s.size(); i++ )
				{
				   if ( ! ( s[ i ] == 'a' || s[ i ] == 'A'
					|| s[ i ] == 'b' || s[ i ] == 'B'
					|| s[ i ] == 'c' || s[ i ] == 'C'
					|| s[ i ] == 'd' || s[ i ] == 'D'
					|| s[ i ] == 'e' || s[ i ] == 'E'
					|| s[ i ] == 'f' || s[ i ] == 'F' 
					|| s[ i ] == '0' || s[ i ] == '1' 
					|| s[ i ] == '2' || s[ i ] == '3' 
					|| s[ i ] == '4' || s[ i ] == '5' 
					|| s[ i ] == '6' || s[ i ] == '7' 
					|| s[ i ] == '8' || s[ i ] == '9' ) )
					 {
						 return false;
					 }
				}
			}
			else
			{
				for ( Uint32 i = 1; i < s.size(); i++ )
				{
					if ( ! ( s[ i ] == '0' || s[ i ] == '1' 
					 || s[ i ] == '2' || s[ i ] == '3' 
					 || s[ i ] == '4' || s[ i ] == '5' 
					 || s[ i ] == '6' || s[ i ] == '7' ) ) 
					{
						return false;
					}
				}
			}
		}
		else
		{
			for ( Uint32 i = 0; i < s.size(); i++ )
			{
				if ( ! ( s[ i ] == '0' || s[ i ] == '1' 
				 || s[ i ] == '2' || s[ i ] == '3' 
				 || s[ i ] == '4' || s[ i ] == '5' 
				 || s[ i ] == '6' || s[ i ] == '7' 
				 || s[ i ] == '8' || s[ i ] == '9' ) )
				{
					return false;
				}
			}
		}

		char* errpos;

		v = strtoul( s.c_str(), &errpos, 0 );

		return true;
	}

	return false;
}

ostream& Tools::printNoXHex32Capital( ostream& o, Uint32 v )
{
	o.fill( '0' );

	o.width( 8 );

	o.flags( ios::right );

	o << uppercase << hex << v << dec << nouppercase;

	o.flags( ios::left );

	o.fill( ' ' );

	return o;
}

ostream& Tools::printNoXHex32( ostream& o, Uint32 v )
{
	o.fill( '0' );

	o.width( 8 );

	o.flags( ios::right );

	o << hex << v << dec;

	o.flags( ios::left );

	o.fill( ' ' );

	return o;
}