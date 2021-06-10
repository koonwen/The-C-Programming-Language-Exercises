// Exercise 5-17
/* Add a field-handling capability, so sorting may be done on fields
   within lines, each field sorted according to an independent set of
   options. (The index for this book was sorted with -df for the
   index category and -n for the page numbers.) */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLEN 1000		/* max length of any input line */
#define MAXLINES 5000		/* max #lines to be sorted */
char *lineptr[MAXLINES];	/* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void myqsort(void *lineptr[], int left, int right,
	     int (*comp)(void *, void *), int reverse);
int numcmp(char *, char *);
int mystrcmp(char *, char *);

static char fold = 0;		/* 1 if fold is specified */
static char directory = 0;	/* 1 if directory is specified */
static int p1 = 0;
static int p2 = 0;		/* field between p1 - p2 are sorted
				   ignoring the rest. if p1 == p2,
				   the lines are sorted by according
				   to the entire line */
/* sort input lines */
int main(int argc, char *argv[])
{
  int nlines;			/* number of input lines read */
  int numeric = 0;		/* 1 if numeric sort */
  int reverse = 0;		/* 1 if reverse order */
  
  for (int i=1; argc-- > 1; i++) {
    if (strcmp(argv[i], "-n") == 0)
      numeric = 1;
    else if (strcmp(argv[i], "-r") == 0)
      reverse = 1;
    else if (strcmp(argv[i], "-f") == 0)
      fold = 1;
    else if (strcmp(argv[i], "-d") == 0)
      directory = 1;
    else if (strcmp(argv[i], "-p") == 0) {
      p1 = atoi(argv[++i]);
      p2 = atoi(argv[++i]);	/* Does not have very good error
				   checking */
      break;
    }
    else {
      printf("error: unrecognized option %s\n", argv[i]);
      return 0;
    }
  }
  
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    myqsort((void **) lineptr, 0, nlines-1,
	    (int (*)(void *, void *))(numeric ? numcmp : mystrcmp), reverse);
      writelines(lineptr, nlines);
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}
  

/* qsort: sort v[left]... v[right] into increasing order */
void myqsort(void *v[], int left, int right,
	     int (*comp)(void *, void *), int reverse)
{
  int i, last;
  void swap(void *v[], int, int);

  if (left >= right)		/* do nothing if array contains */
    return;			/* fewer than two elements */
  swap(v, left, (left + right)/2);
  last = left;
  for (i = left+1; i <= right; i++)
    switch (reverse) {
    case 1:
      if ((*comp)(v[i], v[left]) > 0)
	swap(v, ++last, i);
      break;
    default:
      if ((*comp)(v[i], v[left]) < 0)
	swap(v, ++last, i);
      break;
    }
  swap(v, left, last);
  myqsort(v, left, last-1, comp, reverse);
  myqsort(v, last+1, right, comp, reverse);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
  double v1, v2;

  v1 = atof(s1);
  v2 = atof(s2);
  if (v1 < v2)
    return -1;
  else if (v1 > v2)
    return 1;
  else
    return 0;
}

/* mystrcmp: return <0 if s<t, 0 if s ===t, >0 if s>t */
int mystrcmp(char *s, char *t)
{
  int i;
  
  if (p1 == p2)
    p2 = MAXLEN;
  
  for (i=p2-p1-1, s+=p1, t+=p1; *s != '\0' && i > 0; s++, t++, i--) {
    if (directory) {
      while (!isalpha(*s) && !isspace(*s) && !isdigit(*s))
	s++;
      while (!isalpha(*t) && !isspace(*t) && !isdigit(*t))
	t++;
    }
    if (fold) {
      if (tolower(*s) != tolower(*t))
	return 0;
      return tolower(*s) - tolower(*t);
    } else {
      for ( ; *s == *t; s++, t++)
	if (*s == '\0')
	  return 0;
      return *s - *t;
    }
  }
  return 0;
}

void swap(void *v[], int i, int j)
{
  void *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}



int mygetline(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
  int len, nlines;
  char *p, line[MAXLEN];
  
  nlines = 0;
  while ((len = mygetline(line, MAXLEN)) > 0)
    if (nlines >= maxlines || (p = alloc(len)) == NULL)
      return -1;
    else {
      line[len-1] = '\0'; 	/* delete newline */
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
  int i;

  for (i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
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

#define ALLOCSIZE 10000		/* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;	 /* next free position */

char *alloc(int n)		/* return pointer to n characters */
{
  if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
    allocp += n;
    return allocp - n;		/* old p */
  } else
    return 0;
}
