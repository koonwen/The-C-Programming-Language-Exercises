//Exercise 1-14
/* Write a program to print a histogram of frequencies of different
   characters in its input */

#include <stdio.h>

int main()
{
  int c, cnt, i, j;
  double ascii[255];

  for (i = 0; i < 255; i++)
    ascii[i] = 0;

  cnt = 0;
  while ((c = getchar()) != EOF) {
    ++ascii[c];
    ++cnt;
  }

  for (i = 32; i <= 126; i++) {
    printf("%c: ", i);
    ascii[i] = (ascii[i] / cnt) * 100;
    for (j = (int) ascii[i]; j > 0; j--)
      printf("*");
    printf("\n");
  }

  return 0;
}
