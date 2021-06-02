// Exercise 5-1
/* As written, getint treats a + or - not followed by a digit as a
   valid representation of zero. Fix it to puch such a character back
   on the input. */

#include <ctype.h>
#include <stdio.h>

int getch(void);
void ungetch(int);
int getint(int *);

int main()
{
  int ip;
  printf("Enter your input number:\n");
  if (getint(&ip) > 0)
    printf("ip value is %d\n", ip);
  else
    printf("EOF or Not a number encountered\n");
  return 0;
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
  int c, sign;

  while (isspace(c = getch()))	/* skip white space */
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c);			/* it's not a number */
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-')
    c = getch();
  if (!isdigit(c))
    return 0;
  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  *pn *= sign;
  if (c != EOF)
    ungetch(c);
  return c;
}

/* ==========================BUFFER FUNCTIONS=============================== */
#define BUFSIZE 100

char buf[BUFSIZE];		/* buffer for ungetch */
int bufp = 0;			/* next free position in buf */

/* get a (possibly pushed back) character */
int getch(void)
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c)
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

