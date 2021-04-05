//Exercise 1-21
//Write a program entab that replaces strings of blanks by the minimum number of tabs and blanks to acheive the same spacing. Use the same tab stops as for detab. When either a tab or a single blank would suffice to read a tab stop, which should be give preference?

#include <stdio.h>

#define TABSTOP 8

int main()
{
  int i, c, ntab, nwhite;
  int col = 0;

  nwhite = 1;
  ntab = 0;
  while ((c = getchar()) != EOF) {
    col++;
    
    if (c == ' ') {
      while ((c = getchar()) != EOF && c == ' ') {
	col++;
	if (col % TABSTOP == 0) {
	  nwhite = 0;
	  ntab++;
	}
	else
	  nwhite++;
      }
      col++;
      for (i = 0; i<ntab; i++)
	putchar('\t');
      for (i = 0; i<nwhite; i++)
	putchar('0');
      nwhite = 1;
      ntab = 0;
      putchar(c);
    } else
      putchar(c);
    
  }
  
    return 0;
}
  
