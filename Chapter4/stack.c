// Exercise 4-4
/* Add commands to print the top element of the stack without popping,
   to duplicate it, and to swap the top elements. Add a command to
   clear the stack.
*/

/* Stack implementation and functionality */

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
  push(s2);
  push(s1);
}

/* clears everything from the stack.. acutally just changes the stack pointer */
void clearstk(void)
{
  sp = 0;
  return;
}
  
