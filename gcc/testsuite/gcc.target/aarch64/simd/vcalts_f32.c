/* Test the vcalts_f32 AArch64 SIMD intrinsic.  */

/* { dg-do run } */
/* { dg-options "-save-temps -O3 -ftree-fold-phiopt" } */

#include "arm_neon.h"

#define SIZE 6

extern void abort (void);

volatile float32_t in[SIZE] = { -10.4, -3.14, 0.0, 1.5, 5.3, 532.3 };

int
main (void)
{
  volatile uint32_t expected;
  uint32_t actual;

  int i, j;

  for (i = 0; i < SIZE; ++i)
   for (j = 0; j < SIZE; ++j)
     {
        expected = __builtin_fabs (in[i]) < __builtin_fabs (in[j]) ? -1 : 0;
        actual = vcalts_f32 (in[i], in[j]);

        if (actual != expected)
          abort ();
     }

  return 0;
}

/* { dg-final { scan-assembler "facgt\[ \t\]+\[sS\]\[0-9\]+, ?\[sS\]\[0-9\]+, ?\[sS\]\[0-9\]+\n" } } */
