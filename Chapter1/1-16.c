//Exercise 1-16
/* Revise the main routine of the longest-line program so it will
   correctly print the length of the arbitrarily long input lines, and
   as much as possible of the text. */

#include <stdio.h>
#define MAXLINE 1000    /* maximum input line size */

int mygetline(char line[], int maxline);
void copy(char to[], char from[]);

int main()
{
  int len;                /* current line length */
  int max;                /* maximum length seen so far */
  char line[MAXLINE];     /* current input line */
  char longest[MAXLINE];  /* longest line saved here */

  max = 0;
  while ((len = mygetline(line, MAXLINE)) > 0)
    if (len > max) {
      max = len;
      copy(longest, line);
    }
  if (len == -1) {
    printf("Overflow: %s", line);
    return 0;
  }
  if (max > 0)                  /* there was a line */
    printf("%s", longest);
  return 0;
}

/* getline: read a line into s, return length */
int mygetline(char s[], int lim)
{
  int c, i;

  for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
    s[i] = c;
  if (c == '\n') {
    s[i] = c;
    i++;
  } else if (i == lim-1) {
    s[i] = '\0';
    return -1;
  }
  s[i] = '\0';
  return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
  int i;

  i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}


//UNSURE HOW TO IMPLEMENT THIS PROBLEM
