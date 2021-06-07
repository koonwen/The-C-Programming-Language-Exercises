//Exercise 1-12
/* Write a program that prints its input one word per line */

#include <stdio.h>

int main()
{
  int c;

  while ((c = getchar()) != EOF)
    printf("%c\n", c);
  
  return 0;
}
