// Exercise 4-9
/* Our getch and ungetch do not handle a pushed-back EOF
   correctly. Decide what their properties ought to be if an EOF is
   pushed back, then implement your design.
*/

/* The reason why it doesn't work is because the type of the buffer
   is an unsigned char. Therefore if EOF which is equivalent to -1 is
   passed to it, it will cause an error. */

#include <stdio.h>
#include <stdlib.h>		/* for atof() */

#define MAXOP 100		/* max size of operand or operator */
#define NUMBER '0'		/* signal that a number was found */
#define MATH_FUN '1'		/* signal that a math function was found */
#define ASSIGNMENT '='		/* signal that a variable is to be assigned */
#define VAR 'v'			/* signal that a variable was passed */

int getop(char []);
void push(double);
double pop(void);

void peek(void);		/* peek at top element of the stack: ? */
void duplicate(void);		/* duplicate top element and push onto stack: @ */
void swap(void);		/* swap top two elements: $ */
void clear_stack(void);		/* clear the stack: _ */

double resolve_fun(char []);	/* resolve math function */

void assign_most_rec(double);   /* assign last printed variable to '~' */
void assign_to_var(char);	/* assign variable */
double get_var(char);		/* get variable */
void print_var_array(void);	/* print the variable array */


/* reverse Polish calculator */
int main()
{
  int type;
  double op2;
  char s[MAXOP];
  
  while ((type = getop(s)) != EOF) {
    switch (type) {
    case ASSIGNMENT:
      assign_to_var(s[1]);
      break;
    case VAR:
      push(get_var(s[0]));
      break;
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
      assign_most_rec(pop());	/* store most recent printed value */
      printf("\t%.8g\n", get_var('~'));
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }
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
  printf("error: math function not found\n");
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
  int assign=0;

  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  i = 0;
  if (c == '=')	{		/* handling assignment */
    s[++i] = getch();
    return ASSIGNMENT;
  }
  if (!isdigit(c) && c != '.' && c != '-') {
    if (islower(c) || c == '~')
      return VAR;		/* handling variables */
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
  ungetch(c);
  return NUMBER;
}




/* ==========================BUFFER FUNCTIONS=============================== */
int hold;			/* holding place for ungetch */
int use=0;			/* indicate if hold is being used */

/* get a (possibly pushed back) character */
int getch(void)
{
  if (use) {
    use = 0;
    return hold;
  }
  else
    return getchar();
}

/* push character back on input */
void ungetch(int c)
{
  if (use)
    printf("ungetch: too many characters\n");
  else {
    use = 0;
    hold = c;
  }
}

/* push back entire string onto input. Specifically the buffer */
void ungets(char s[])
{
  for (int i=0; i != '\0'; i++)
    ungetch(s[i]);
  return;
} 

/* ==========================VAR ARRAY FUNCTIONS=============================== */
double pop(void);

double var_array[27];		/* array to hold variables a-z, last position
				   holds most recent printed */

/* assign a val in the last position in the var_array */
void assign_most_rec(double val)
{
  var_array[26] = val;
  return;
}

/* assign top of the stack to a given variable between a-z */
void assign_to_var(char v)
{
  if (!islower(v)) {
    printf("error: can only assign to variables between a-z\n");
    return;
  }
  var_array[v - 'a'] = pop();
  printf("Assigned %c=%f\n", v, var_array[v - 'a']);
  return;
}

/* get specific variable value */
double get_var(char v)
{
  if (v == '~')
    return var_array[26];
  else
    return var_array[v-'a'];
}

/* printer for the variable array */
void print_var_array(void)
{
  printf("|");
  for (int i=0; i<27; i++)
    printf(" %f ", var_array[i]);
  printf("|\n");
  return;
}
