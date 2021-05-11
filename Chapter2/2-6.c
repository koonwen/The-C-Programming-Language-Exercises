// Exercise 2-6
/* Write a function setbits(x,p,n,y) that returns x with the n bits that begin
   at position p set to the rightmost n bits of y, leaving the other bits 
   unchanged */

#include <stdio.h>
#include <assert.h>

unsigned getbits(unsigned x, int p, int n);
unsigned dropbits(unsigned x, int n);
unsigned setbits(unsigned x, int p, int n, unsigned y);

int main()
{
  unsigned x = 9;               // 00001001
  unsigned y = 22;              // 00010110
  unsigned z = setbits(x, 1, 2, y);
  assert(z == 21);              // setbits(x, 1, 2, y) -> expected = 00010101
  printf("%d\n", z);              // 00010101 = 21
  return 0; 
}

unsigned getbits(unsigned x, int p, int n)
{
  return (x >> (p+1-n)) & ~(~0 << n);
}

unsigned dropbits(unsigned x, int n)
{
  return x & (~0 << n);
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
  unsigned _x = getbits(x, p, n);
  unsigned _y = dropbits(y, n);
  return _x | _y;    
}
