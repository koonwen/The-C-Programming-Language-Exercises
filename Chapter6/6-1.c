// Exercise 6-1
/* Our version of getword does not properly handle underscores,
   string constants, comments, or processor control lines. Write a
   beter version. */

/* i.e. Need to handle:
   _
   "string constants"
   //comments
   #define <>
*/

#include <stdio.h>
#include <ctype.h>

#define MAXWORD 100

int getword(char *, int);

int main()
{
  int tmp;
  char word[MAXWORD];
  while ((tmp = getword(word, MAXWORD)) != EOF)
    if (tmp > 0)
      printf("%s\n", word);
  return 0;
}

/* getword: get next word or character from input and handle
   underscores, string constants, comments, or processor control
   lines */
int getword(char *word, int lim)
{
  int c, tmp;
  char *w = word;

  while (isspace(c = getc(stdin)) || c == '\n')
    ;
  
  switch (c) {
  case EOF:			/* End of file reached */
    *w = '\0';
    return EOF;
  case '"':			/* handle string constants */
    while ((c = getc(stdin)) != '"')
      ;
    return 0;
  case '/':			/* handle comments */
    if ((c = getc(stdin)) == '/')
      while ((c = getc(stdin)) != '\n')
	;
    else if (c == '*')
      while (1) {
	c = getc(stdin);
	tmp = getc(stdin);
	if (c == '*' && tmp == '/')
	  break;
	else
	  ungetc(tmp, stdin);
      }
    else
      ungetc(c, stdin);
    return 0;
  case '#':			/* handle processor control lines */
    while ((c = getc(stdin)) != '\n')
      ;
    return 0;
  default:			/* collect word */
    if (isalpha(c)) {
      for (*w++ = c; isalnum(c = getc(stdin)); )
	*w++ = c;
      ungetc(c, stdin);
      *w = '\0';
      return 1;
    }
  }
  *w = '\0';
  return 0;
}
