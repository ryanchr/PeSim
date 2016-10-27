
%{
/* C-style lexor. */

#include <stdio.h>
#include <stdlib.h>

#include "core_host.h"
#include "core_misc.h"
#include "core_libexo.h"

/* maximum size token (including strings) for lex */
#undef YYLMAX
#define YYLMAX	(16*1024)

/* disable interactive features, as they are non-portable */
#define YY_NEVER_INTERACTIVE	1

unsigned line = 1;		/* line of last recognized token */

int input();
static void lex_eat_comment(void);

%}

%s BLOB_MODE
%p 3000

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
C1			"/"
C2			"*"
P			(~|!|@|#|\$|%|\^|&|\*|-|\+|\||\/|\?)

%%

<BLOB_MODE>{H}{H}			{ return lex_byte; }

<INITIAL>{C1}{C2}			{ lex_eat_comment(); }

<INITIAL>[\-]?0[xX]{H}+			{ return lex_address; }
<INITIAL>[\-]?0{D}+			{ return lex_integer; }
<INITIAL>[\-]?{D}+			{ return lex_integer; }

<INITIAL>[\-]?{D}+{E}			{ return lex_float; }
<INITIAL>[\-]?{D}*"."{D}+({E})?		{ return lex_float; }
<INITIAL>[\-]?{D}+"."{D}*({E})?		{ return lex_float; }

<INITIAL>'(\\.|[^\\'])+'		{ return lex_char; }

<INITIAL>\"(\\.|[^\\"])*\" /*"*/	{ return lex_string; }

<INITIAL>{L}({L}|{D})*			{ return lex_token; }

<INITIAL>{P}+				{ return lex_token; }

<INITIAL>"{"				{ return '{'; }
<INITIAL>"}"				{ return '}'; }
<INITIAL>","				{ return ','; }
<INITIAL>"("				{ return '('; }
<INITIAL>")"				{ return ')'; }
<INITIAL>"["				{ return '['; }
<INITIAL>"]"				{ return ']'; }
<INITIAL>"<"				{ BEGIN(BLOB_MODE); return '<'; }
<BLOB_MODE>">"				{ BEGIN(INITIAL); return '>'; }

[ \t\v\f]				{ /* nada */; }
[\n]					{ line++; }
<<EOF>>					{ return lex_eof; }
.					{ /* bogus char */
					  fatal("bogus character in input"); }

%%


static void
lex_eat_comment(void)
{
  char c, c1;

loop:
  while ((c = input()) != '*' && c != 0)
    {
      if (c == '\n')
	line++;
    }

  if ((c1 = input()) != '/' && c1 != 0)
    {
      unput(c1);
      goto loop;
    }
}

int
yy_nextchar(void)
{
  int c;

  do {
    c = input();
  } while (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\n');
  unput(c);

  return c;
}

/* FIXME: this is a total KLUDGE (but well contained...) that I will someday
   address when I have copious amounts of free time... */
void
yy_setstream(FILE *stream)
{
  int i;
#define MAX_STREAMS	16
  static struct {
    FILE *stream;
    YY_BUFFER_STATE buffer;
  } streams[MAX_STREAMS] = { {NULL, NULL}, };
  static int num_streams = 0;
  static FILE *last_stream = NULL;

  /* same stream? */
  if (stream == last_stream)
    return;

  /* else, switch to new stream */
  for (i=0; i < num_streams; i++)
    {
      if (streams[i].stream == stream)
	{
	  yy_switch_to_buffer(streams[i].buffer);
	  return;
	}
    }

  /* hrmmm... not found, create a new buffer for this stream */
  if (num_streams == MAX_STREAMS)
    fatal("out of lex buffer streams, increase MAX_STREAMS");

  streams[num_streams].stream = stream;
  streams[num_streams].buffer = yy_create_buffer(stream, YY_BUF_SIZE);
  yy_switch_to_buffer(streams[num_streams].buffer);
  num_streams++;
}
