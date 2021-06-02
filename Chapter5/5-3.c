// Exercise 5-3
/* Write a pointer version of the function strcat that we showed in
   Chapter 2: strcat(s,t) copies the string t to the end of s. */

#include <stdio.h>

void pstrcat(char *, char *);

int main()
{
  char s[20] = "hello ";
  char *t = "world";

  pstrcat(s, t);
  printf("%s", s);

  return 0;
}


void pstrcat(char *s, char *t)
{
  while (*s++)
    ;
  s--;
  while ((*s++ = *t++))
    ;
  return;
}
