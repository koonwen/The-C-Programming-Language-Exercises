// Exercise 5-19
/* Modify undcl so that it does not add redundant parentheses to
   declarations */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

void ungettoken(char *);
int gettoken(void);
int tokentype;			/* type of last token */
char token[MAXTOKEN];		/* last token string */
char name[MAXTOKEN];		/* identifier name */
char datatype[MAXTOKEN];	/* data type = char, int, etc. */
char out[1000];			/* output string */
char err = 0;			/* holds err status */

int main()			/* convert word description to declaration */
{
  int type;
  char temp[MAXTOKEN];

  while (gettoken() != EOF) {
    strcpy(out, token);
    while ((type = gettoken()) != '\n')
	   if (type == PARENS || type == BRACKETS)
	     strcat(out, token);
	   else if (type == '*') {
	     if ((type = gettoken()) == NAME) {
	       sprintf(temp, "*%s", out);
	       ungettoken(token);
	       continue;
	     }
	     ungettoken(token);
	     sprintf(temp, "(*%s)", out);
	     strcpy(out, temp);
	   } else if (type == NAME) {
	     sprintf(temp, "%s %s", token, out);
	     strcpy(out, temp);
	   } else
	     printf("invalid input at %s\n", token);
    printf("%s\n", out);
  }
  return 0;
}

void ungettoken(char *p)
{
  int i = strlen(p)-1;
  for (p = p + i; i >= 0; i--)
    ungetc(*p--, stdin);
}	 

int gettoken(void)		/* return next token */
{
  int c;
  char *p = token;

  while ((c = getc(stdin)) == ' ' || c == '\t')
    ;
  if (c == '(') {
    if ((c = getc(stdin)) == ')') {
      strcpy(token, "()");
      return tokentype = PARENS;
    } else {
      ungetc(c, stdin);
      return tokentype = '(';
    }
  } else if (c == '[') {
    for (*p++ = c; (*p++ = getc(stdin)) != ']'; )
      ;
    *p = '\0';
    return tokentype = BRACKETS;
  } else if (isalpha(c)) {
    for (*p++ = c; isalnum(c = getc(stdin)); )
      *p++ = c;
    *p = '\0';
    ungetc(c, stdin);
    return tokentype = NAME;
  } else
    return tokentype = c;
}

