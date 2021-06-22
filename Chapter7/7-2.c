// Exercise 7-2
/* Write a program that will print arbritrary input in a sensible
   way. As a minimum, it should print non-graphic characters in octal
   or hexadecimal according to local custom, and break long text
   lines */

#include <stdio.h>
#include <ctype.h>

#define MAXLEN 4

int main()
{
  int c;
  int h = 0, o = 0;  

  while ((c = getchar()) != EOF)
    if (c == '\\') {
      c = getchar();
      switch (c) {
      case 'n':
	putchar('\n');
	break;
      case 'x':
	while ((c = getchar()) != ' ' || c != '\n')
	  h = h * 16 + (c - '0');
	printf("%d", h);
	ungetc(c, stdin);
	h = 0;
	break;
      case 'o':
	while ((c = getchar()) != ' ' || c != '\n')
	  o = o * 8 + (c - '0');
	printf("%d", o);
	ungetc(c, stdin);
	o = 0;
	break;
      default:
	printf("Unrecognized escape sequence\n");
	return 0;
      }
    } else
      putchar(c);
  return 0;
}
    
