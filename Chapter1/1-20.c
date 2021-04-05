//Exercise 1-20
//Write a program detab that replaces tabs in the input with the proper number of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns. Should n be a variable or a symbolic parameter?

#include <stdio.h>

#define TABSTOPS 8

int main()
{
  int c, i, col, fix;

  col = 0;
  while ((c = getchar()) != EOF) {

    col = (1+col) % TABSTOPS;
    
    if (c == '\t') {
      putchar(' ');
      for (i=col; i<TABSTOPS; i++)
	putchar(' ');
      col = 0;
    } else 
      putchar(c);
  }
  
  return 0;
}

//Ans: symbolic parameter
