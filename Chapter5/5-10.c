// Exercise 5-10
/* Write the program expr, which evaluates a reverse Polish
   expresssion from the command lne, where each operator or operand
   is a separate argument, For example,
expr 2 3 4 + *
evaluates 2 X (3+4). */

#include <stdio.h>
#include <stdlib.h>		/* for atof() */
#include <ctype.h>

void push(double);
double pop(void);
void printstack(void);

/* Rudimentary reverse Polish calculator with only +*-/ functions and
   no error checking */
int main(int argc, char *argv[])
{
  int type;
  double op2;

  while (*++argv)
    if (!isdigit(type = **argv))
      switch (type) {
      case '+':
	push(pop() + pop());
	break;
      case '*':
	push(pop() * pop());
	break;
      case '-':
	op2 = pop();
	push(pop() - op2);
	break;
      case '/':
	op2 = pop();
	push(pop() / pop());
	break;
      default:
	printf("expr: illegal operator %c\n", **argv);
	return 0;
      }
    else
      push(atof(*argv));

  printf("Ans: %f\n", pop());
  return 0;
}

/* ==========================STACK FUNCTIONS=============================== */
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

void printstack(void)
{
  for (int i = sp-1; i>=0; i--)
    printf("%f ", val[i]);
  return;
}
  
