//Exercise 1-2
/* What happens when \c is used when c is not {n,t,b,\,",}
\n : newline
\t : tab
\b : backspace
\\ : \
\" : "
*/

#include <stdio.h>

int main()
{
  char *s = "\H\e\l\l\o \W\o\r\l\d";
  printf("%s", s);
  return 0;
}


//Ans: For characters without a known escape sequence, no output is produced.
