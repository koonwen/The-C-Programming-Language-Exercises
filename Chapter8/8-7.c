// Exercise 8-7
/* malloc accepts a size request without checking it's plausibility; free
   believes that the block it is asked to free contains a valid size
   field. Improve these routines so they take more pains with error checking */

#include <math.h>

#define MAXSIZE pow(2,32);

/* malloc: general-purpose storage allocator */
void *malloc(unsigned nbytes)
{
  Header *p, *prevp;
  Header *morecore(unsigned);	/* function to request space from OS */
  unsigned nunits;

  /* check to see if size is reasonable */
  if (nbytes > MAXSIZE) {
    fprintf(stderr, "malloc: error, cannot alloc size %lu\n", nbytes);
    return NULL;
  }

  /* The -1 is so that if it fits exactly we don't allocate more than
     required. The / division always performs floor division */
  nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;
  if ((prevp = freep) == NULL) { /* no free list yet, create degenerate list */
    base.s.ptr = freep = prevp = &base; /* point to itself itself */
    base.s.size = 0;
  }
  for (p = prevp->s.ptr; ;prevp = p, p = p->s.ptr) { /* move along linked list */
    if (p->s.size >= nunits) {			     /* big enough */
      if (p->s.size == nunits)			     /* exactly */
	prevp->s.ptr = p->s.ptr;
      else {
	p->s.size -= nunits;
	p += p->s.size;
	p->s.size = nunits;
      }
      freep = prevp;
      return (void *)(p+1);
    }
    if (p == freep)		/* wrapped around free list */
      if ((p = morecore(nunits)) == NULL)
	return NULL;
  }
}

/* free: put block ap in free list */
void free(void *ap)
{
  Header *bp, *p;

  bp = (Header *)ap - 1;	/* point to block header */
  if (bp->s.size = 0 || bp->s.size > MAXSIZE) {
    fprintf(stderr, "free: error, invalid size field %lu\n", bp->s.size);
    return;
  }
  for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) /* while not in
							       between p and p->s.ptr */
    if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) /* wrap around and address
						       is beyond
						       starting/ending of list */
      break;			/* freed block at start or end of arena */

  if (bp + bp->s.size == p->s.ptr) { /* join to upper nbr */
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  } else
    bp->s.ptr = p->s.ptr;
  if (p + p->s.size == bp) {	/* join to lower nbr */
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
  } else
    p->s.ptr = bp;
  freep = p;
}
