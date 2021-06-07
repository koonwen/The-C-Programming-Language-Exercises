//Exercise 1-17
/* Write a program to print all input lines that are longer than 80
   characters */

#include <stdio.h>

#define MIN 80
#define MAXSIZE 1000

int mygetline(char line[], int lim);

int main()
{
  int len;
  char line[MAXSIZE];

  while ((len = mygetline(line, MAXSIZE)) > 0) {
    if (len > MIN)
      printf("%s", line);
  }
  return 0;
}


int mygetline(char s[], int lim)
{
  int i, c;

  for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
    s[i] = c;
  if (c == '\n') {
    s[i] = c;
    i++;
  }
  s[i] = '\0';
  return i;
}
