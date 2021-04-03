//Exercise 1-13
//Wrtie a program to print a histogram of the length of words in its input. It is easy to draw the histogram with the bars horizontal;  vertical orientation is more challenging

#include <stdio.h>

int main()
{
  int c, cnt, i, j;
  int state;
  int len[20];

  for (i = 0; i < 20; i++)
    len[i] = 0;

  cnt = 1;
  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\n' || c == '\t' || c < 'A' || (c > 'Z' && c < 'a') || c > 'z')
      cnt = 1;
    else {
      --len[cnt-1];
      ++len[cnt++];
    }
  }

  printf("My Horizontal  Historgram:\n");
  for (i = 1; i < 20; i++) {
    printf("%d: ", i);
    for (j = len[i]; j > 0; j--)
      printf("*");
    printf("\n");
  }

  int max = 0;
  for (i = 1; i < 20; i++) {
    if (len[i] > max)
      max = len[i];
  }
  
  printf("My Vertical Histogram:\n");
  for (i = max; i > 0; i--) {
    for (j = 1; j < 20; j++) {
      if (len[j] != 0) {
	len[j]--;
	printf("*");
      }
      else
	printf(" ");
    }
    printf("\n");
  }
  
  return 0;
}
