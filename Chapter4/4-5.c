// Exercises 4-5
/* Add access to library functions like sin, exp and pow. See <math.h>
   in Appendix B, Section 4
*/

#include <stdio.h>
#include <stdlib.h>		/* for atof() */

#define MAXOP 100		/* max size of operand or operator */
#define NUMBER '0'		/* signal that a number was found */
#define MATH_FUN '1'		/* signal that a math function was found */

int getop(char []);
void push(double);
double pop(void);

void peek(void);		/* peek at top element of the stack: ? */
void duplicate(void);		/* duplicate top element and push onto stack: @ */
void swap(void);		/* swap top two elements: $ */
void clear_stack(void);		/* clear the stack: _ */

double resolve_fun(char []);	/* resolve math function */

/* reverse Polish calculator */
int main()
{
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
    switch (type) {
    case MATH_FUN:
      push(resolve_fun(s));
      break;
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      op2 = pop();
      push(pop() + op2);
      break;
    case '*':
      op2 = pop();
      push(pop() * op2);
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0)
	push(pop() / op2);
      else
	printf("error: zero divisor\n");
      break;
    case '%':
      op2 = pop();
      if(op2 != 0.0)
	push((long) pop() % (long) op2); /* cannot do modulus on doubles */
      else
	printf("error: zero divisor\n");
      break;
    case '?':			/* peek at top element */
      peek();
      break;
    case '@':			/* duplicate top element */
      duplicate();
      break;
    case '$':			/* swap top two elements */
      swap();
      break;
    case '_':			/* clear the stack */
      clear_stack();
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }
  return 0;
}

/* =====================STACK FUNCTIONS ===================== */
#define MAXVAL 100		/* maximum depth of val stack */

int sp = 0;			/* next free stack position */
double val[MAXVAL];		/* value stack */

/* push: push f onto value stack */
void push(double f)
{
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from the stack */
double pop(void)
{
  if (sp > 0)
    return val[--sp];
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

/* get head of the stack */
void peek(void)
{
  if (sp == 0)
    printf("Stack empty\n");
  else
    printf("PEEKING: %f\n", val[sp-1]);
  return;
}

/* duplicate top head of the stack and push it onto the stack */
void duplicate(void)
{
  double dup = val[sp-1];
  push(dup);
}

/* swap top two elements */
void swap(void)
{
  double s1, s2;
  s1 = pop();
  s2 = pop();
  push(s1);
  push(s2);
}

/* clears everything from the stack.. acutally just changes the stack
   pointer */
void clear_stack(void)
{
  sp = 0;
  return;
}

/* ==========================MATH FUNCTIONS=============================== */
#include <math.h>
#include <string.h>

double pop(void);

/* execute specified math functions */
double resolve_fun(char s[])
{
  if (strcmp(s, "SIN") == 0)
    return sin(pop());
  if (strcmp(s, "EXP") == 0)
    return exp(pop());
  if (strcmp(s, "POW") == 0) {
    double op = pop();
    return pow(pop(), op);
  }
  printf("error: math function not found");
  return -1;
}

/* ==========================INPUT HANDLING=============================== */
#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand  */
int getop(char s[])
{
  int i, c;

  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  i = 0;
  if (!isdigit(c) && c != '.' && c != '-') {
    if (isupper(c)) {
      while (isupper(s[++i] = c = getch()))
	;
      s[i] = '\0';
      if (c != EOF)
	ungetch(c);
      return MATH_FUN;		/* math function */
    }
    return c;			/* not a number */
  }
  i = 0;
  if (c == '-')			/* provisions for negative values */
    c = s[++i] = getch();
  if (isdigit(c))		/* collect integer part */
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.')			/* collect fraction part */
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  if (c != EOF)
    ungetch(c);
  return NUMBER;
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
