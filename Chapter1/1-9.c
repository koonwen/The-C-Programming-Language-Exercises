//Exercise 1-9
//Write a program to copy its input to its output, replacing each string of one or more blanks by a single blank

#include <stdio.h>

int main()
{
  int c, b;
  b = ' ';

  while ((c = getchar()) != EOF) {
    if (c == ' '){
      while (c == ' ')
	c = getchar();
      putchar(b);
    }
    putchar(c);
  }
  
  return 0;
}
