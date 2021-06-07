// Exercise 5-11.c
/* Modify the programs entab and detab (written as exercises in
   Chapter 1) to accept a list of tabstops as arguments. Use the
   default tab settings if there are no arguments */

#include <stdio.h>
#include <stdlib.h>

#define STARTING 1
#define TABSTOPS 8

void detab(int, int);
void entab(int, int);

static int m = STARTING;
static int n = TABSTOPS;

int main() {
  /* uncomment to test */
  //entab(m, n);
  //detab(m, n);
  return 0;
}  

/* void detab: convert '\t' in input as number of white spaces in
   output. */
void detab(int m, int n)
{
  int c, cnt, inc;
  
  for (cnt=1; (c = getchar()) != EOF; cnt++) {
    if (c == '\n')
      cnt = 0;
    if (c == '\t' && cnt >= (m-1)*n)
      for(inc = n - (cnt % n), cnt += inc; inc-- >= 0;)
	putchar(' ');
    else
      putchar(c);
  }
}

/* void entab: convert whitespace to \t where appropriate. */
void entab(int m, int n)
{
  int c, cnt, inc;

  for (cnt=1; (c = getchar()) != EOF; cnt++) {
    if (c == '\n')
      cnt = 0;
    if (c == ' ' && cnt >= (m-1)*n) {
      for(++cnt; (c = getchar()) == ' '; cnt++)
	if (cnt % n == 0){
	  putchar('\\');
	  putchar('t');
	}
      inc = cnt % n;
      while(--inc)
	putchar(' ');
    } 
    putchar(c);
  }
}
      
	  
