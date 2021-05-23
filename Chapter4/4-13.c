// Exercise 4-13
/* Write a recursive version of the function reverse(s), which
   reverses the string s in place.
 */

#include <stdio.h>
#include <string.h>

void reverse(char []);

int main()
{
  char s[] = "hello";
  reverse(s);
  printf("The string is now %s\n", s);
  return 0;
}

void reverse(char s[])
{
  void reverser(char s[], int left, int len);

  reverser(s, 0, strlen(s)-1);
}

void reverser(char s[], int left, int right)
{
  if (left >= right)
    return;

  reverser(s, left+1, right-1);
  int tmp = s[left];
  s[left] = s[right];
  s[right] = tmp;
}
