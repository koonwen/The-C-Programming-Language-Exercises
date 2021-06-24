// Exercise 7-7
/* Modify the pattern finding program in Chapter 5 to taken its input
   from a set of named files or, if no files are named as arguments,
   from the standard input. Should the file name be printed when
   a matching line is found? */

// Ans: of course! Filename needs to be printed otherwise the program
// is effectively useless when multiple files are provided

#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int find_helper(char *, size_t, FILE *, char *, char *, int, int);

/* find: print lines that match pattern from 1st arg */
int main(int argc, char *argv[])
{
  char line[MAXLINE];
  int c, except = 0, number = 0, found = 0;
  char *pattern;
  FILE *fp = stdin;

  while (--argc > 0 && (*++argv)[0] == '-')
    while ((c = *++argv[0]))
      switch (c) {
      case 'x':
	except = 1;
	break;
      case 'n':
	number = 1;
	break;
      default:
	printf("find: illegal option %c\n", c);
	argc = 0;
	found = -1;
	break;
      }
  if (argc < 1)
    printf("Usage: find -x -n pattern\n");
  else {
    pattern = *argv;
    for (argv++; *argv != NULL; argv++)
      if ((fp = fopen(*argv, "r")) == NULL)
	break;
      else
	found += find_helper(line, MAXLINE, fp, *argv, pattern, number, except);
  }
  return found;
}


int find_helper(char *line, size_t max, FILE *fp, char *filename, char *pattern, int number, int except)
{
  long lineno = 0;
  int found = 0;

  while (getline(&line, &max, fp) > 0) {
    lineno++;
    if ((strstr(line, pattern) != NULL) != except) {
      if (number)
	printf("%s %ld:", filename, lineno);
      printf("%s", line);
      found++;
    }
  }
  return found;
}
