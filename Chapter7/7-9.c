// Exercise 7-9
/* Functions like isupper can be implemented to save space or to save
   space or to save time. Explore both possibilities */

#include <stdio.h>
#include <ctype.h>

/* This is more time efficient because it is just an inline macro
   expansion */
#define isupper_time(c) (c >= 'A' && c <= 'Z')

/* this is more space efficient because space is only used when the
   function is called */
int isupper_space(int *c)
{
  return (*c >= 'A' && *c <= 'Z')
}

/* Take note that isupper_time should not be used with pointers and it is
   designed that way becasue the inline expansion may result in
   unexpected behaviour as such


   char *s = "string";

   while (isupper_time(*s++))
        ;


EVALUATES TO:

   while (*s++ >= 'A' && *s++ <= 'Z')       WRONG
         ;

   which increments s twice.

*/
