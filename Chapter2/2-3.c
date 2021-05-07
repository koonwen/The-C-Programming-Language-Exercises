// Exercise 2-3
/* Write a function htoi(s), which converts a string of hexadecimal digits
(including an optional 0x or 0X) into its equivalent integer value. The 
allowable digits are 0 through 9, a through f, and A through F */

#include <stdio.h>
#include <ctype.h>

int htoi(char s[]);

int main()
{
  char s[] = "0x12a4";
  int n = htoi(s);
  printf("conversion of hexadecimal %s to decimal int = %d", s, n);
  
  return 0;
}

int htoi(char s[])
{
  int i, n, tmp;
  n = 0;
  i = 0;
  
  if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
    i = 2;

  for (; isdigit(s[i]) || (s[i] >= 'a' && s[i] <= 'f') || (s[i] >= 'A' && s[i] <= 'F'); i++)
    {
      if (isdigit(s[i]))
	tmp = s[i] - '0';
      else if (s[i] >= 'a' && s[i] <= 'f')
	tmp = s[i] - 'a' + 11;
      else
	tmp = s[i] - 'A' + 11;
           
      n = n * 16 + tmp;
    };
  return n;
}
