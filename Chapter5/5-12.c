// Exercise 5-12.c
/* Extend entab and detab to accept the shorthand
   entab -m +n
   to mean tab stops every n columns, starting at column m. Choose
   convenient (for the user) default behaviour */

#include <stdio.h>
#include <stdlib.h>

#define STARTING 1
#define TABSTOPS 8
#define NAN(v, p) if (v == 0) { printf("detab: error not a number %s\n", p); return 0;}

void detab(int, int);
void entab(int, int);

int main(int argc, char *argv[])
{
  int m = STARTING;
  int n = TABSTOPS;

  while (*++argv){
    switch (**argv) {
    case '-':
      m = atoi(++*argv);
      NAN(m, *argv);
      break;
    case '+':
      n = atoi(++*argv);
      NAN(n, *argv);
      break;
    default:
      printf("detab: error flag %c\n", **argv);
      return 0;
    }
  }
  /* uncomment to test */
  //detab(m, n);
  //entab(m, n);
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
