/* { dg-do compile } */
/* { dg-do run } */

#include <stdlib.h>
typedef struct
{
  int a;
  float b;
}str_t;

#ifdef STACK_SIZE
#if STACK_SIZE > 16000
#define N 1000
#else
#define N (STACK_SIZE/16)
#endif
#else
#define N 1000
#endif

typedef struct 
{
  str_t * sub_str;
  int c;
}str_with_substr_t;

int foo;

int
main (void)
{
  int i;
  str_with_substr_t A[N];
  str_t a[N];

  for (i=0; i < N; i++)
    A[i].sub_str = &(a[i]);

  for (i=0; i < N; i++)
    A[i].sub_str->a = 5;

  foo = A[56].sub_str->a;

  return 0;
}

/*--------------------------------------------------------------------------*/
/* { dg-final { scan-ipa-dump "has escaped...Type is used in an array" "struct_reorg" } } */
