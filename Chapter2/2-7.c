// Exercise 2-7
/* Write a function invert(x, p, n) that returns x with the n bits that begin
   at position p inverted (i.e., 1 changed into 0 and vice versa), leaving the 
   others unchanged */

#include <stdio.h>
#include <assert.h>
#include "binfunction.h"

unsigned invert(unsigned x, int p, int n);

int main()
{
  unsigned x = 36;                       // 00100100
  unsigned result = invert(x, 5, 3);     // 00111000
  assert(result == 56);
  printf("%d\n", result);
  return 0;
}

unsigned invert(unsigned x, int p, int n)
{
  unsigned y = ~0;
  unsigned front = dropbits(x, p);
  unsigned middle = (p-n+1) << ~setbits(x, p, n, y);
  unsigned back = getbits(x, p-n-1, p-n-1);
  printf("front = %d, middle = %d, back = %d\n", front, middle, back);
  return front | middle | back;
}
