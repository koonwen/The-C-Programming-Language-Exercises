// Exercise 5-4
/* Write the function strend(s,t), which returns 1 if the string t
   occurs at the end of the string s, and zero otherwise */

#include <stdio.h>

int strend(char *, char *);

int main()
{
  char *s = "hello hello";
  char *t = "llo";

  if (strend(s, t))
    printf("true\n");
  else
    printf("false\n");
  return 0;
}

int strend(char *s, char *t)
{
  char *start = t;
  while (*s++)
    ;
  while (*t++)
    ;
  while (*--t == *--s)
    if (t == start)
      return 1;
  return 0;
}
