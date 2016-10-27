#ifndef ME_TOOLS_H
#define ME_TOOLS_H

#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

#include "types.h"

#define MAX( X, Y ) ( ( ( X ) > ( Y ) ) ? ( X ) : ( Y ) )
#define MIN( X, Y ) ( ( ( X ) < ( Y ) ) ? ( X ) : ( Y ) )
#define MIN3( X, Y, Z ) ( ( ( X ) < ( Y ) ) ? ( ( ( X ) < ( Z ) ) ? ( X ) : ( Z ) ) : ( ( ( Y ) < ( Z ) ) ? ( Y ) : ( Z ) ) )
#define MAX3( X, Y, Z ) ( ( ( X ) > ( Y ) ) ? ( ( ( X ) > ( Z ) ) ? ( X ) : ( Z ) ) : ( ( ( Y ) > ( Z ) ) ? ( Y ) : ( Z ) ) )

class Tools
{
 public:
 	static int print2file(FILE *fp, const char *fmt, ...);
	static ostream& printHex( ostream& o, Uint32 v );
	static ostream& printHex( ostream& o, Uint32 v, int w );
	static ostream& printHex04( ostream& o, Uint32 v );
	static ostream& printHex08( ostream& o, Uint32 v );
	static ostream& printHex12( ostream& o, Uint32 v );
	static ostream& printHex16( ostream& o, Uint32 v );
	static ostream& printHex24( ostream& o, Uint32 v );
	static ostream& printHex32( ostream& o, Uint32 v );
	static ostream& printDec( ostream& o, const Uint32 v, int w = 10 );
	static ostream& printDec( ostream& o, const Sint32 v, int w = 10 );
	static ostream& printDec( ostream& o, const Sint64 v, int w = 20 );
	static ostream& printBin32( ostream& o, Uint32 v );
	static bool StringToUint32( string& s, Uint32& v );
	static string Uint32ToString( Uint32 v );
	static void Uint32ToString( Uint32 v, string& s );
	static ostream& printNoXHex32( ostream& o, Uint32 v );
	static ostream& printNoXHex32Capital( ostream& o, Uint32 v );
};

#endif

