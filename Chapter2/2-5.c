// Exercise 2-5
/* Write the function any(s1, s2), which returns the first location in the string s1 where any character from the string
s2 occurs, or -1 if s1 contains no characters from s2. (The standard library function strpbrk does the same job but
returns a pointer to the location.) */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

int any(char s1[], char s2[]);
  
int main()
{
  char *p;
  int d;
  
  char s1[] = "hello";
  char s2[] = "oh";

  p = strpbrk(s1, s2);  
  d = any(s1, s2);

  if (p == NULL) {
    assert(d == -1);
    printf("any returned index %d, strpbrk returned NULL pointer\n", d);
  }
  else {
    assert(s1[d] == *p);
    printf("any returned index %d, strpbrk returned pointer to %c\n", d, *p);
  }
  
  return 0;
}

int any(char s1[], char s2[])
{
  int i, j, n;
  n = INT_MAX;
  
  for (i=0; s2[i] != '\0'; i++)
    for (j=0; j<n && s1[j] != '\0'; j++)
      if (s1[j] == s2[i])
	n = j;

  if (n == INT_MAX)
    return -1;
  
  return n;
}
