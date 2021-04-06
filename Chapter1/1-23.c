//Exercise 1-23
//Write a program to remove all comments from a C program. Don't forget to handle quoted strings and character constants properly. C comments do not nest.

#include <stdio.h>

int main()
{
  int c, n;

  while ((c = getchar()) != EOF) {
    
    if (c == '/') {
      n = getchar();
      if (n == '/')
	while ((c = getchar()) != EOF && c != '\n')
	  ;
      else if (n == '*')
	while ((c = getchar()) != EOF) {
	  if (c == '*') {
	    n = getchar();
	    if (n == '/')
	      break;
	  }
	}
      else {
	putchar(c);
	putchar(n);
      }
    }
    if (c == EOF)
      break;
    
    if (c == '*' && n == '/')
      continue;
    n = 0;
    putchar(c);
  }
  
  return 0;
}
