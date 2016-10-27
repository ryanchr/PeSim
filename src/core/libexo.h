#ifndef EXO_H
#define EXO_H

#include "host.h"
#include "misc.h"
#include "machine.h"

/* EXO file format versions */
#define EXO_FMT_MAJOR		1
#define EXO_FMT_MINOR		0

/* EXO term classes, keep this in sync with EXO_CLASS_STR */
enum exo_class_t {
  ec_integer,			/* EXO int value */
  ec_address,			/* EXO address value */
  ec_float,			/* EXO FP value */
  ec_char,			/* EXO character value */
  ec_string,			/* EXO string value */
  ec_list,			/* EXO list */
  ec_array,			/* EXO array */
  ec_token,			/* EXO token value */
  ec_blob,			/* EXO blob (Binary Large OBject) */
  ec_null,			/* used internally */
  ec_NUM
};

/* EXO term classes print strings */
extern char *exo_class_str[ec_NUM];

/* EXO token table entry */
struct exo_token_t {
  struct exo_token_t *next;	/* next element in a hash buck chain */
  char *str;			/* token string */
  int token;			/* token value */
};

struct exo_term_t {
  struct exo_term_t *next;	/* next element, when in a list */
  enum exo_class_t ec;		/* term node class */
  union {
    struct as_integer_t {
      exo_integer_t val;		/* integer value */
    } as_integer;
    struct as_address_t {
      exo_address_t val;		/* address value */
    } as_address;
    struct as_float_t {
      exo_float_t val;			/* floating point value */
    } as_float;
    struct as_char_t {
      char val;				/* character value */
    } as_char;
    struct as_string_t {
      unsigned char *str;		/* string value */
    } as_string;
    struct as_list_t {
      struct exo_term_t *head;		/* list head pointer */
    } as_list;
    struct as_array_t {
      int size;				/* size of the array */
      struct exo_term_t **array;	/* list head pointer */
    } as_array;
    struct as_token_t {
      struct exo_token_t *ent;		/* token table entry */
    } as_token;
    struct as_blob_t {
      int size;				/* byte size of object */
      unsigned char *data;		/* pointer to blob data */
    } as_blob;
  } variant;
};
/* short-cut accessors */
#define as_integer	variant.as_integer
#define as_address	variant.as_address
#define as_float	variant.as_float
#define as_char		variant.as_char
#define as_string	variant.as_string
#define as_list		variant.as_list
#define as_array	variant.as_array
#define as_token	variant.as_token
#define as_blob		variant.as_blob

/* EXO array accessor, may be used as an L-value or R-value */
/* EXO array accessor, may be used as an L-value or R-value */

/* intern token TOKEN_STR */
struct exo_token_t *
exo_intern(char *token_str);		/* string to intern */

/* intern token TOKEN_STR as value TOKEN */
struct exo_token_t *
exo_intern_as(char *token_str,		/* string to intern */
	      int token);		/* internment value */

/*
 * create a new EXO term, usage:
 *
 *	exo_new(ec_integer, (exo_integer_t)<int>);
 *	exo_new(ec_address, (exo_address_t)<int>);
 *	exo_new(ec_float, (exo_float_t)<float>);
 *	exo_new(ec_char, (int)<char>);
 *      exo_new(ec_string, "<string>");
 *      exo_new(ec_list, <list_ent>..., NULL);
 *      exo_new(ec_array, <size>, <array_ent>..., NULL);
 *	exo_new(ec_token, "<token>");
 *	exo_new(ec_blob, <size>, <data_ptr>);
 */
struct exo_term_t *
exo_new(enum exo_class_t ec, ...);

/* release an EXO term */
void
exo_delete(struct exo_term_t *exo);

/* chain two EXO lists together, FORE is attached on the end of AFT */
struct exo_term_t *
exo_chain(struct exo_term_t *fore, struct exo_term_t *aft);

/* copy an EXO node */
struct exo_term_t *
exo_copy(struct exo_term_t *exo);

/* deep copy an EXO structure */
struct exo_term_t *
exo_deepcopy(struct exo_term_t *exo);

/* print an EXO term */
void
exo_print(struct exo_term_t *exo, FILE *stream);

/* read one EXO term from STREAM */
struct exo_term_t *
exo_read(FILE *stream);

/* lexor components */
enum lex_t {
  lex_integer = 256,
  lex_address,
  lex_float,
  lex_char,
  lex_string,
  lex_token,
  lex_byte,
  lex_eof
};

#endif /* EXO_H */
