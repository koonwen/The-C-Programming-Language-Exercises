//Exercise 1-18
//Write a program to remove trailing blanks and tabs from each line of input, and to delete entirely blank lines

#include <stdio.h>

#define MAXLINE 1000

int mygetline(char line[], int maxline);
void remove_space(char line[], int last);

int main()
{
  int len;
  char line[MAXLINE];

  while ((len = mygetline(line, MAXLINE)) > 0) {
    if (len == 1)
      continue;
    remove_space(line, len-1);
    if (line[0] == '\0')
      continue;
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


void remove_space(char s[], int l)
{
  while (s[--l] == ' ' || s[--l] == '\t') {
    s[l] = s[l+1];
    if (l == 0)
      break;
  }
}
  
