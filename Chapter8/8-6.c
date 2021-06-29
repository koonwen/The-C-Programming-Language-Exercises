// Exercise 8-6
/* The standard library function calloc(n, size) returns a pointer to n objects
   of size 'size', with the storage initialized to zero. Write calloc, by
   calling malloc or by modifying it. */

#include <stdio.h>
#include <stdlib.h>

void *mycalloc(unsigned);	/* nowadays size_t is used because it is
				   machine dependent */

int main()
{
  int *i = (int *) mycalloc(sizeof(int));
  printf("%d\n", *i);
}


void *mycalloc(unsigned nbytes)
{
  char *p, *vp;
  vp = p = (char *) malloc(nbytes);
  while (nbytes-- > 0)
    *p++ = 0;
  return (void *)vp;
}
