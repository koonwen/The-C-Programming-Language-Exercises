// Exercise 5-6
/* Rewrite appropriate programs from earlier chapters and exercises
   with pointers instead of array indexing. Good possibilities
   include getline (Chapters 1 and 4), atoi, itoa, and their variants
   (Chapters 2, 3 and 4), reverse (Chapter 3), and strindex and getop
   (Chapter 4) */

#define swap(type, a, b) {type tmp = *a; *a++ = *b; *b-- = tmp;}

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int getline_p(char *);
int atoi_p(char *);
char *itoa_p(int);
void reverse_p(char *);
int strindex_p(char *, char *);
int getop_p(char *);

int main()
{
  char buf[BUFSIZ];
  printf("Give your number input here: \n");
  getline_p(buf);
  printf("%s\n", buf);
  
  int hold = atoi_p(buf);
  printf("value as an integer is: %d\n", hold);

  printf("String value is: \"%s\"\n", itoa_p(hold));

  printf("Give your reversable input here: \n");
  getline_p(buf);
  reverse_p(buf);
  printf("reversed input is: %s\n", buf);

  char s[] = "hello world";
  char t[] = "orl";
  printf("strindex returns index %d comparing %s and %s\n", strindex_p(s, t), s, t);

  printf("getop returned: %c\n", getop_p(buf));
  printf("\'%s\' inside buffer\n", buf);
  
  return 0;
}

/* getline_p: read a line into s, return length */
int getline_p(char *buf)
{
  char *start = buf;

  for (;(*buf = getchar())!=EOF && *buf!='\n'; buf++)
    ;
  *buf = '\0';
  return buf - start;
}

/* atoi_p: convert s to integer without sign */
int atoi_p(char *s)
{
  int v = 0;
  while (*s != '\0')
    v = v * 10 + (*s++ - '0');
  return v;
}

/* itoa_p: convert positive integer to s without sign */
char *itoa_p(int v)
{
  static char buf[BUFSIZ];
  static char *s = buf, *e = buf;
  
  char hold = '0' + v % 10;
  if (v / 10 > 1) {
    e++;
    itoa_p(v / 10);
  } else
    *++e = '\0';
    
  *s++ = hold;
  return buf;
}
    
/* reverse_p: reverse a string in place */
void reverse_p(char *s)
{
  char *e = s + strlen(s) - 1;
  
  while (s < e)
    swap(char, s, e);

  return;
}

/* strindex_p: finds the index of the starting point where t is a
   substring of s. Otherwise returns -1 */
int strindex_p(char *s, char *t)
{
  char *beg = s;
  char *start_s = s;
  char *start_t = t;
   
  while (*s != '\0') {
    if (*s == *t) {
      for (start_s = s; *++t == *++s;) {
	if (*(t+1) == '\0')
	  return start_s - beg;
      }
      s = start_s + 1;
      t = start_t;
    }
    else
      s++;
  }  

  return -1;
}


#define NUMBER '0'

/* int getop_p: get next operator or operand */
int getop_p(char *s)
{
  int c;
  
  while ((*s = c = getc(stdin)) == ' ' || c == '\t')
    ;
  *(s+1) = '\0';
  if (!isdigit(*s) && *s != '.')
    return c;			/* not a number */
  if (isdigit(c))		/* collect integer part */
    while (isdigit(*++s = c = getc(stdin)))
      ;

  if (c == '.')			/* collect fraction part */
    while (isdigit(*++s = c = getc(stdin)));

  *s = '\0';
  if (c != EOF)
    ungetc(c, stdin);
  return NUMBER;
}
