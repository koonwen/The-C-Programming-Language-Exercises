// Exercise 5-2
/* Write getfloat, the floating-point analog of getint. What type
   does getfloat return as its function value? */

/* Ans: still returns int signal but arguments is a double pointer */

#include <ctype.h>
#include <stdio.h>
#include <math.h>

int getch(void);
void ungetch(int);
int getfloat(double *);

int main()
{
  double d;
  printf("Enter your float here:\n");
  if (getfloat(&d) > 0)
    printf("Value of float is %f\n", d);
  else
    printf("EOF or not a number encountered\n");
  return 0;
}

int getfloat(double *dp)
{
  int c, sign, cnt;
  double dec;

  while (isspace(c = getch()))
    ;
  if (!isdigit(c) && c != EOF && c != '-' && c != '+') {
    ungetch(c);
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-') 
    c = getch();
  if (!isdigit(c))
    return 0;
  for (*dp=0; isdigit(c) && c != '.'; c = getch())
    *dp = *dp * 10 + (c - '0');
  if (c == '.') {
    c = getch();
    for (dec = 0, cnt = 0; isdigit(c) && c != EOF; c = getch(), cnt++)
      dec = dec * 10 + (c - '0');
    dec /= pow(10, cnt);
    *dp = *dp + dec;
  }
  *dp *= sign;
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
