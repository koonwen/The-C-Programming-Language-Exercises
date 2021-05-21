// Exercise 4-4
/* Add commands to print the top element of the stack without popping,
   to duplicate it, and to swap the top elements. Add a command to
   clear the stack.
*/

#include <stdio.h>
#include "stack.h"

#define MAXVAL 100		/* stack pointer */

int sp = 0;			/* stack pointer */
double val[MAXVAL];		/* stack size */

double peek(void);
void duplicate(void);
void swap(void);
void clearstk(void);

/* get head of the stack */
double peek(void)
{
  return val[sp];
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
  
