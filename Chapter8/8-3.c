// Exercise 8-3 (*Note, could note test, MacOSX does not provide UNIX standard
// fiel descriptor interface)
/* Design and write _flushbuf, fflush and fclose */

#include "syscalls.h"

/* _flushbuf: allocate and flush output buffer */
int _flushbuf(int x, FILE *fp)
{
  unsigned nc;
  int bufsize;

  if (fp < _iob || fp >= _iob + OPEN_MAX)
    return EOF;
  if ((fp->flag & (_WRITE | _ERR)) != _WRITE)
    return EOF;
  bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
  if (fp->base == NULL) {
    if ((fp->base = (char *) malloc(bufsize)) == NULL) {
      fp->flag |= _ERR;
      return EOF;
    }
  } else {
    nc = fp->ptr - fp->base;
    if (write(fp->fd, fp->base, nc) != nc) {
      fp->flag |= _ERR;
      return EOF;
    }
  }
  fp->ptr = fp->base;
  *fp->ptr++ = (char) x;
  fp->cnt = bufsize - 1;
  return x;
}

/* fclose: close file */
int fclose(FILE *fp)
{
  int rc;

  if ((rc = fflush(fp)) != EOF) {
    free(fp->base);
    fp->ptr = NULL;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag &= ~(_READ | _WRITE);
  }
  return rc;
}


/* fflush: flush buffer associated with file fp */
int fflush(FILE *fp)
{
  int rc;
  if (fp < _iob || fp >= _iob + OPEN_MAX)
    return EOF;
  if (fp->flag & _WRITE)
    rc = _flushbuf(0, fp);
  fp->ptr = fp_base;
  fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
  return rc;
}

