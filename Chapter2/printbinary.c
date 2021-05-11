#include <stdio.h>
#include <math.h>

#define BITS_PER_BYTE 8
#define BIN_BASE 2

void printbin(unsigned x);

int main()
{
  printbin(25);
  return 0;
}

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
