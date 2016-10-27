#include "core_endian.h"
#ifndef HOST_ONLY
#include "loader.h"
#endif

/* probe host (simulator) byte endian format */
enum endian_t
endian_host_byte_order(void)
{
  int i = 1, *p;

  p = &i;
  if (*((char *)p) == 1)
    return endian_little;
  else if (*((char *)p) == 0)
    return endian_big;
  else
    return endian_unknown;
}

/* probe host (simulator) double word endian format */
enum endian_t
endian_host_word_order(void)
{
  int *p;
  double x = 1.0;

  /* NOTE: this check assumes IEEE floating point format */
  p = (int *)&x;
  if (*p == 0)
    return endian_little;
  else if (*p == 0x3ff00000)
    return endian_big;
  else
    return endian_unknown;
}

#ifndef HOST_ONLY

/* probe target (simulated program) byte endian format, only
   valid after program has been loaded */
enum endian_t
endian_target_byte_order(void)
{
  return ld_target_big_endian ? endian_big : endian_little;
}

/* probe target (simulated program) double word endian format,
   only valid after program has been loaded */
enum endian_t
endian_target_word_order(void)
{
  /* same as byte sex for SimpleScalar target */
  return endian_target_byte_order();
}

#endif /* !HOST_ONLY */
