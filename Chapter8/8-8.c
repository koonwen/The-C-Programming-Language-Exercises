// Exercise 8-8
/* Write a routine bfree(p, n) that will free an arbritrary block p of n
   characters into the free list maintained by malloc and free. By using bfree,
   a user can add a static or external array to the free list at any time */

#include <stdio.h>

typedef long Align;

union header {
  struct {
    union header *ptr;
    unsigned size;
  };
  Align x;
};

typedef union header Header;

static base Header;
static Header *freep;

/* We will create the header inside the arbritray block. Therefore the size
   that we can work with is smaller than the actual arrary provided */
void bfree(void *ap, unsigned n)
{
  Header *p, *bp;

  if (n <= sizeof(Header)) {
    fprintf(stderr, "bfree: error, block size too small");
    return;
  }

  bp = (Header *) ap;		/* new Header for arbritrary block */
  bp->s.size = n - sizeof(Header);

  for (p = freep; !(p < bp && bp < p->s.ptr); p = p->s.ptr)
    if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
      break;

  /* We will not attempt to coalesce arbritrary blocks that users apply bfree
     to */
  bp->s.ptr = p->s.ptr;
  p->s.ptr = bp;
  return;
}
