#include <stdio.h>
#include <math.h>

#define BITS_PER_BYTE 8
#define BIN_BASE 2


void printbin(unsigned x);
unsigned getbits(unsigned x, int p, int n);
unsigned dropbits(unsigned x, int n);
unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned invert(unsigned x, int p, int n);

void printbin(unsigned x)
{
  int b = BITS_PER_BYTE;
  int tmp;
  
  while (pow(BIN_BASE, b) < x)
    x += BITS_PER_BYTE;
  int binarr[x];
  
  for (int i=b-1; i>=0; i--) {
    tmp = pow(2, i);
    if (tmp > x) {
      printf("0");
      continue;
    }    
    x -= tmp;
    binarr[i] = 1;
    printf("1");
  }
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

unsigned invert(unsigned x, int p, int n)
{
  unsigned y = ~0;
  unsigned front = dropbits(x, p);
  unsigned middle = (p-n+1) << ~setbits(x, p, n, y);
  unsigned back = getbits(x, p-n-1, p-n-1);
  printf("front = %d, middle = %d, back = %d\n", front, middle, back);
  return front | middle | back;
}
