// Exercise 5-5
/* Write versions of the library functions strncpy, strncat, and
   strncmp, which operate on at most the first n characters of their
   argument strings. For example, strncpy(s, t, n) copies at most n
   characters of t to s. Full descriptions are in Appendix B. */

#define p(string) printf("%s\n", string)

#include <stdio.h>

void mystrncpy(char destination[], char *to_copy, size_t n);
void mystrncat(char destination[], char *to_cat, size_t n);
int mystrncmp(char *s, char *t, size_t n);

int main()
{
  char s[100];
  char *t = "hello";
  mystrncpy(s, t, 7);
  p(s);
  mystrncat(s, t, 7);
  p(s);
  if (mystrncmp(s, t, 6))
    p("true");
  else
    p("false");

  return 0;
}


void mystrncpy(char des[], char *cpy, size_t n)
{
  while (n--) {
    *des++ = *cpy++;
    if (*cpy == '\0') {
      *des = '\0';
      return;
    }
  }
  return;
}

void mystrncat(char des[], char *cat, size_t n)
{
  while (*des++)
    ;
  des--;
  while (n--) {
    *des++ = *cat++;
    if (*cat == '\0') {
      *des = '\0';
      return;
    }
  }
  return;
}

int mystrncmp(char *s, char *t, size_t n)
{
  while (--*n)
    if (*s++ != *t++)
      return 0;
  return 1;
}
  
