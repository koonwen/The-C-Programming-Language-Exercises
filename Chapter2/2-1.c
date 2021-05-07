//Exercise 2-1.
// Write a program to determine the ranges of char, short, int, and long variables, both signed and unsigned, by printing appropriate values from standard headers and by direct computation. Harder if you compute them: determine the ranges of the various floating-point-types,

#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

int main()
{
  
  printf("signed char number of bits: %.f, range: %d - %d\n", log2(UCHAR_MAX+1), CHAR_MIN, CHAR_MAX);
  printf("signed short number of bits %.f, range: %d - %d\n", log2(USHRT_MAX+1), SHRT_MIN, SHRT_MAX);
  printf("signed int number of bits %.f, range: %d - %d\n", log2(UINT_MAX), INT_MIN, INT_MAX);
  printf("singed long number of bits %.f, range: %ld - %ld\n", log2(ULONG_MAX), LONG_MIN, LONG_MAX);

  return 0;
}
