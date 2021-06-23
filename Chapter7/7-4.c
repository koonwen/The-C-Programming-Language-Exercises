// Exercuse 7-4
/* Write a private version of scanf analogous to minprintf from the
   prvious section */

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

#define MAXLEN 100

int minscanf(char *fmt, ...);

int main()
{
  char month[20];
  int day;
  int year;
  minscanf("%d %s %d", &day, month, &year);
  printf("%d %s %d", day, month, year);
  return 0;
}


int minscanf(char *fmt, ...)
{
  va_list ap;
  int ival;
  char *sval, *p;
  int c;
  
  va_start(ap, fmt);
  for (p = fmt; *p; p++) {
    if (*p != '%') {
      if (*p != getchar())
	return p - fmt;
      continue;
    }
    switch (*++p) {
    case 'd':
      for (ival = 0; isdigit(c = getchar());)
	ival = ival * 10 + (c - '0');
      *va_arg(ap, int *) = ival;
      ungetc(c, stdin);
      break;
    case 's':      
      for (sval = va_arg(ap, char *); isalpha(c = getchar()); sval++)
	*sval = c;
      *++sval = '\0';
      ungetc(c, stdin);
      break;
    }
  }
  return p - fmt;
}
     
      
      
	
	
