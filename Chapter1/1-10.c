//Exercise 1-10
//Write a program to copy its input to its output, replacing each tab by \t, each backspace by \b, and each backslash by \\. This makes tabs and backspaces visible in an unambiguous way.

#include <stdio.h>

int main()
{
  char c, t, b, bs;
  t = '\t';
  b = '\b';
  bs = '\\';

  while ((c = getchar()) != EOF) {
    if (c == t) {
      putchar('\\');
      putchar('t');
      continue;
    }
    if (c == b) {
      putchar('\\');
      putchar('b');
      continue;
    }
    if (c == bs) {
      putchar('\\');
      putchar('\\');
      continue;
    }
    putchar(c);
  }

  return 0;
}
