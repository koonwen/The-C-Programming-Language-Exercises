// Exercise 4-14
/* Define a macro swap(t,x,y) that interchanges two arguments of
   type t. (Block structure will help) */

#include <stdio.h>

#define swap(t,x,y) t tmp = y; y = x; x = tmp;

int main()
{
  int x = 9;
  int y = 15;
  swap(int, x, y);
  printf("Does my swap work? x = %d, y = %d\n", x, y);
  return 0;
}
