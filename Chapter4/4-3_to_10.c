// Exercise 4-3
/*
  Given the basic framwork. it's straightforward to extend the
  calculator. Add the modulus (operator) and provisions for negative
  numbers.
*/

// Exercise 4-4
/* Add commands to print the top element of the stack without popping,
   to duplicate it, and to swap the top elements. Add a command to
   clear the stack.
*/

// Exercises 4-5
/* Add access to library functions like sin, exp and pow. See <math.h>
   in Appendix B, Section 4 */

#include <stdio.h>
#include <stdlib.h>       /* for atof() */
#include <math.h>     /* for sin(x), exp(x) and pow(x, y) functions */

#define MAXOP 100	         /* max size of operand or operator */
#define NUMBER '0'	       /* signal that a number was found */

#define PEEK 'P'
#define DUPLICATE 'D'
#define SWAP 'S'
#define CLEAR 'C' 

#define SIN '1'		       /* signal that sin(x) to be executed */
#define EXP '2'		       /* signal that exp(x) to be executed */
#define POW '3'		       /* signal that pow(x) to be executed */

int getop(char []);
void push(double);
double pop(void);
double peek(void);
void duplicate(void);
void swap(void);
void clearstk(void);


/* reverse Polish calculator */
int main()
{
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
    switch (type) {
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
	push((int) pop() % (int) op2); /* Cannot do modulus on doubles */
      else
	printf("error: zero divisor\n");
      break;
    case SIN:
      push(sin(pop()));
      break;
    case EXP:
      push(exp(pop()));
      break;
    case POW:
      op2 = pop();
      push(pow(op2, pop()));
      break;
    case PEEK:
      printf("\t%.8g\n", peek());
      break;
    case DUPLICATE:
      duplicate();
      break;
    case SWAP:
      swap();
      break;
    case CLEAR:
      clearstk();
      break;
    case '\n':
      printf("\t%.8g\n", peek());
      fflush(stdout);
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
    printf("PEEKING: %f\n", peek());
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
double peek(void)
{
  if (sp == 0)
    printf("Stack empty\n")
    return 0.0;
  else
    return val[sp-1];
}

/* duplicate top head of the stack and push it onto the stack */
void duplicate(void)
{
  double dup = peek();
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
void clearstk(void)
{
  sp = 0;
  return;
}

/* ==========================INPUT HANDLING=============================== */
#include <ctype.h>
#include <string.h>   /* for strcmp */


int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand  */
int getop(char s[])
{
  int i, c;
  int paranthesis = 0;

  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  i = 0;
  if (c == '(') {		/* provision for negative numbers (-423) or (4040) allowed */
    paranthesis = 1;
    c = getch();
    if (c == '-')
      s[0] = c, c = getch(), s[1] = c, i = 1;
    else
      s[0] = c;
  }
  if (!isdigit(c) && c != '.') {
    if (c == 'P' || c == 'D' || c == 'S' || c == 'C')       /* peek, duplicate, swap, clear functions */
      return c;
    char s[4];
    s[0]=c, s[3]='\0';
    s[1] = getchar();
    s[2] = getchar();
    if (strcmp(s, "sin") == 0)
      return '1';
    if (strcmp(s, "exp") == 0)
      return '2';
    if (strcmp(s, "pow") == 0)
      return '3';
    ungetch(s[2]);
    ungetch(s[1]);
    return c;			/* not a number */
  }
  if (isdigit(c))		/* collect integer part */
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.')			/* collect fraction part */
    while (isdigit(s[++i] = c = getch()))
      ;
  if (paranthesis) {
    if (c != ')')
      return c;
    else
      c = getch();
  }
  s[i] = '\0';
  if (c != EOF)
    ungetch(c);
  return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];		/* buffer for ungetch */
int bufp = 0;			/* next free position in buf */

int getch(void)			/* get a (possibly pushed back) character */
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)		/* push character back on input */
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
