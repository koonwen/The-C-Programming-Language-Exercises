// Exercise 4-12
/* Adapt the ideas of printd to write a recursive version of itoa;
   that is, convert an integer into a string by calling a recursive
   routine. */

#include <stdio.h>

void itoa(int, char []);

int main()
{
  int n = 500;
  char s[4];
  itoa(n, s);
  printf("I have the string %s\n", s);
  return 0;
}

void itoa(int n, char s[])
{
  static int i;
  if (n < 0)
    s[i++] = '-', n -= -1;

  if (n/10) {
    itoa(n/10, s);
  } else
    s[i] = '\0';
  s[i++] = n % 10 + '0';
}
  
