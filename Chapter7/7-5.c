// Exercise 7-5
/* Rewrite the postfix calculator of Chapter 4 to use scanf and/or
   sscanf to do the input the number conversion */

#include <stdio.h>
#include <stdlib.h>		/* for atof() */

#define MAXOP 100		/* max size of operand or operator */
#define NUMBER '0'		 /* signal that a number was found */

int getop(double *);
void push(double);
double pop(void);

/* reverse Polish calculator */
int main()
{
  int type;
  double op, op2;

  while ((type = getop(&op)) != EOF) {
    switch (type) {
    case NUMBER:
      push(op);
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
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("error: unknown command %c\n", type);
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


/* ==========================INPUT HANDLING=============================== */
#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand  */
int getop(double *op)
{
  char c;
  int n;

  if ((n = getchar()) == '\n')
    return n;
  ungetc(n, stdin);
  if (scanf("%lg", op) > 0)
    return NUMBER;
  else if (scanf("%c", &c) > 0)
    return c;
  return EOF;
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
