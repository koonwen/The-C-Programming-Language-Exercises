//Exercise 1-22.c
/* Write a program to "fold" long input lines into two or more shorter
   lines after the last non-blank character that occurs before the
   n-th column of input. Make sure your program does something
   intelligent with very long lines, and if there are no blanks or
   tabs before the specified column. */

#include <stdio.h>

#define MAXLINE 1000       /* Maximum input of line */
#define COL 10             /* Column break */
#define SEARCH_LIM 5       /* The maximum that the program will search
			      for a blank before breaking works with a
			      - */

int mygetline(char line[], int maxline);
void fold(char line[], int len);

static char buffer[MAXLINE];

int main()
{
  int len;
  char line[MAXLINE];

  while ((len = mygetline(line, MAXLINE)) > 0) {
    fold(line, len);
    printf("%s", line);
  }
  
  return 0;
}


int mygetline(char s[], int lim)
{
  int c, i;

  for(i=0; i<lim-1 && (c = getchar()) != '\n' && c != EOF; i++)
    s[i] = c;

  if (c == '\n')
    s[i++] = '\n';
  
  s[i] = '\0';

  return i;
}
    

void fold(char s[], int len)
{  
  if (len <= COL)
    return;

  int i = COL;
  //int j = SEARCH_LIM;

  while (i <= len) {   
    
    while (s[i] != ' ' && s[i] != '\t') 
      i--;
    
    s[i] = '\n';
    i += COL;
  }
  return;
}


//Have not implemented the hyphening function.
