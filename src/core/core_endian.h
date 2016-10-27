#ifndef ENDIAN_H
#define ENDIAN_H

/* data swapping functions, from big/little to little/big endian format */
#define SWAP_HALF(X)							\
  (((((half_t)(X)) & 0xff) << 8) | ((((half_t)(X)) & 0xff00) >> 8))
#define SWAP_WORD(X)	(((word_t)(X) << 24) |				\
			 (((word_t)(X) << 8)  & 0x00ff0000) |		\
			 (((word_t)(X) >> 8)  & 0x0000ff00) |		\
			 (((word_t)(X) >> 24) & 0x000000ff))
#define SWAP_QWORD(X)	(((qword_t)(X) << 56) |				\
			 (((qword_t)(X) << 40) & ULL(0x00ff000000000000)) |\
			 (((qword_t)(X) << 24) & ULL(0x0000ff0000000000)) |\
			 (((qword_t)(X) << 8)  & ULL(0x000000ff00000000)) |\
			 (((qword_t)(X) >> 8)  & ULL(0x00000000ff000000)) |\
			 (((qword_t)(X) >> 24) & ULL(0x0000000000ff0000)) |\
			 (((qword_t)(X) >> 40) & ULL(0x000000000000ff00)) |\
			 (((qword_t)(X) >> 56) & ULL(0x00000000000000ff)))

/* recognized endian formats */
enum endian_t { endian_big, endian_little, endian_unknown};
/* probe host (simulator) byte endian format */
enum endian_t
endian_host_byte_order(void);

/* probe host (simulator) double word endian format */
enum endian_t
endian_host_word_order(void);

#ifndef HOST_ONLY

/* probe target (simulated program) byte endian format, only
   valid after program has been loaded */
enum endian_t
endian_target_byte_order(void);

/* probe target (simulated program) double word endian format,
   only valid after program has been loaded */
enum endian_t
endian_target_word_order(void);

#endif /* HOST_ONLY */

#endif /* ENDIAN_H */
