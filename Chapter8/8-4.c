// Exercise 8-4  (*Note, could note test, MacOSX does not provide UNIX standard
// fiel descriptor interface)
/* The standard library function
   int fseek(FILE *fp, long offset, int origin)
   is identical to lseek except that fp is a file pointer instead of a file
   descriptor and the return value is an int status not a position. Write
   fseek. Make sure that your fseek coordinates properly with the buffering
   done for the other functions of the library */

#include <fcntl.h>
#include <syscalls.h>

int fseek(FILE *fp, long offset, int origin)
{
  unsigned nc;
  long rc = 0;

  if (fp->flag & _READ) {
    if (origin == 1)
      offset -= fp->cnt;
    rc = lseek(fp->fd, offset, origin);
    fp->cnt = 0;
  } else if (fp->flag & _WRITE) {
    if ((nc = fp->ptr - fp->base) > 0)
      if (write(fp->fd, fp->base, nc) != nc)
	rc = -1;
    if (rc != -1)
      rc = lseek(fp->fd, offset, origin);
  }
  return (rc == 1) ? -1 : 0;
}
