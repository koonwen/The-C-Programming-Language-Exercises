// Exercise 5-13
/* Write the program tail, which prints the last n lines of its
   input. By default, n is 10, let us say, but it can be chnaged by
   an optional argument, so that
   tail -n
   prints the last n lines. The program should behave rationally no
   matter how unreasonable the input or the value of n. Write the
   program so it makes the best use of available storage; lines
   should be stored as in the sorting program of Section 5.6, not in
   a two-dimensional array of fixed size. */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
#define DEFAULT 10

void mytail(int);

int main(int argc, char *argv[])
{
  int n;
  
  if (argc == 1) {
    mytail(DEFAULT);
  }
  else if (argc == 2) {
    if ((*++argv)[0] == '-') {
      n = atoi(++*argv);
      if (n > 0)
	mytail(n);
      else
	printf("tail: Illegal option %s\n", *argv);
    } else
      printf("tail: Usage -val\n");
  }
  
  return 0;
}
  
void mytail(int n)
{
  char **pca = (char **) malloc(n * sizeof(char *));
  char **starting_p = pca, **ending_p;
  char *line = NULL;
  size_t linecapp = MAXLINE;
  
  while (getline(&line, &linecapp, stdin) >= 0) {
    if (pca > starting_p+n) {
      *(pca = starting_p) = line;
      pca++;
    }
    else
      *pca++ = line;

    line = NULL;
  }
  
  for (ending_p = pca, pca++; pca != ending_p; pca++)
    if (pca > starting_p + n)
      pca = starting_p;
    else if (*pca == NULL)
      continue;
    else
      printf("%s", *pca);
}
