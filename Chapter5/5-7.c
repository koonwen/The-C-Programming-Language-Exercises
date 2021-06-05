// Exercise 5-7
/* Rewrite readlines to store lines in an array supplied by main
   rather than calling alloc to maintain storage. How much faster is
   the program? */

#include <stdio.h>
#include <string.h>


#define MAXLINES 5000		/* max #lines to be sorted */
#define MAXLEN 1000		/* max length of any input line */

char *lineptr[MAXLINES];	/* pointers to test lines */
char store[MAXLINES * MAXLEN];	/* large array to store the actual
				   lines */

int readlines(char store[], char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main()
{
  int nlines;			/* number of input lines read */

  if ((nlines = readlines(store, lineptr, MAXLINES)) >= 0) {
    qsort(lineptr, 0, nlines-1);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return 1;
  }
}

int mygetline(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *store, char *lineptr[], int maxlines)
{
  int len, nlines;
  char line[MAXLEN];
  char *spMAX = store+MAXLINES+MAXLEN;

  nlines = 0;
  while ((len = mygetline(line, MAXLEN)) > 0)
    if (nlines >= maxlines || store + len > spMAX)
      return -1;
    else {
      line[len-1] = '\0'; 	/* delete newline */
      lineptr[nlines++] = store;
      store = stpcpy(store, line)+1;
    }
  return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
  while (nlines-- > 0)
    printf("%s\n", *lineptr++);
}

/* mygetline: read a line into s, return length */
int mygetline(char s[], int lim)
{
  int c, i;

  for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
    s[i] = c;
  if (c== '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}

/* #define ALLOCSIZE 10000		/\* size of available space *\/ */

/* static char allocbuf[ALLOCSIZE]; /\* storage for alloc *\/ */
/* static char *allocp = allocbuf;	 /\* next free position *\/ */

/* char *alloc(int n)		/\* return pointer to n characters *\/ */
/* { */
/*   if (allocbuf + ALLOCSIZE - allocp >= n) { /\* it fits *\/ */
/*     allocp += n; */
/*     return allocp - n;		/\* old p *\/ */
/*   } else */
/*     return 0; */
/* }  */

/* qsort: sort v[left]... v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
  int i, last;
  void swap(char *v[], int i, int j);

  if (left >= right)		/* do nothing if array contains */
    return;			/* fewer than two elements */
  swap(v, left, (left + right)/2);
  last = left;
  for (i = left+1; i <= right; i++)
    if (strcmp(v[i], v[left]) < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  qsort(v, left, last-1);
  qsort(v, last+1, right);
}

/* sort: interchange routine needs only trivial changes */
void swap(char *v[], int i, int j)
{
  char *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
