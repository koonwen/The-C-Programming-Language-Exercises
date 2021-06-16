// Exercise 5-18
/* Make dcl recover from input errors */
/* My modifications to the code only propogates errors to the user
   more clearly and allows the user to re-enter input in a more
   intuitive manner */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;			/* type of last token */
char token[MAXTOKEN];		/* last token string */
char name[MAXTOKEN];		/* identifier name */
char datatype[MAXTOKEN];	/* data type = char, int, etc. */
char out[1000];			/* output string */
char err = 0;			/* holds err status */

int main()			/* convert declaration into words */
{
  while (gettoken() != EOF) {	/* 1st token on line */
    strcpy(datatype, token);	/* is the datatype */
    out[0] = '\0';
    dcl();			/* parse rest of the line */
    if (tokentype != '\n') {
      err = 1, printf("syntax error\n");
      while (getchar() != '\n')
	;
    }
    if (err){
      err = 0;
      printf("Please re-enter input:\n");
      continue;
    } else
      printf("%s: %s %s\n", name, out, datatype);
  }
  return 0;
}

/* dcl: parse a declarator */
void dcl(void)
{
  int ns;

  for (ns = 0; gettoken() == '*';) /* count *'s */
    ns++;
  dirdcl();
  while (ns-- > 0)
    strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
  int type;

  if (tokentype == '(') {	/* (dcl) */
    dcl();
    if (tokentype != ')')
      err = 1, printf("error: missing )\n");
  } else if (tokentype == NAME)	/* variable name */
    strcpy(name, token);
  else
    err = 1, printf("error: expected name or (dcl)\n");
  while ((type=gettoken()) == PARENS || type == BRACKETS)
    if (type == PARENS)
      strcat(out, " function returning");
    else {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
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

