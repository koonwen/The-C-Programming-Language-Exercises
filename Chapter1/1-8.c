//Exercise 1-8
/* Write a program to count blanks tabs and newlines */

#include <stdio.h>

int main()
{
  int c, b, t, nl;

  b = 0;
  t = 0;
  nl = 0;
  while ((c = getchar()) != EOF) {
    if (c == ' ')
      b++;
    if (c == '\n')
      nl++;
    if (c == '\t')
      t++;
  }

  printf("\nBlanks: %d, Tabs: %d, Newlines: %d\n", b, t, nl);

  return 0;
}
