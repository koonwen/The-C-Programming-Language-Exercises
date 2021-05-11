// Exercise 2-8
/* Write a funtion rightrot(x,n) that returns the value of the integer x rotated to the right by n bit positions. */

#include <stdio.h>
#include "binfunction.h"

unsigned rightrot(unsigned x, int n);

int main()
{
  unsigned x = 25;
  x = rightrot(25, 5);
  printf("%u",x);
  return 0;
}

unsigned rightrot(unsigned x, int n)
{
  int unsign_bits = sizeof(unsigned) * 8;
  unsigned right = getbits(x, n-1, n) << (unsign_bits-n);
  unsigned left = dropbits(x, n);
  return right | left;
}
