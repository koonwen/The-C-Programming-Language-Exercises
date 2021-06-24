// Exercise 7-8
/* Write a program to print a set of files, starting each new one on
   a new page, with a title and a running page count for each file. */

#include <stdio.h>
#include <stdlib.h>

void cat(FILE *);
  
int main(int argc, char *argv[])
{
  FILE *fp;
  char *prog = argv[0];		/* program name for errors */
  
  for (int cnt = 1; *++argv != NULL; cnt++) {
    printf("\n\n\n%50s ---%s (Page %d):---\n", "",*argv, cnt);
    if ((fp = fopen(*argv, "r")) == NULL) {
      fprintf(stderr, "%s: could not read file %s\n", prog, *argv);
      exit(1);
    }
    cat(fp);
    fclose(fp);
  }
  exit(0);
}


void cat(FILE *fp)
{
  int c;
  while ((c = getc(fp)) != EOF)
    putchar(c);
  
  if (ferror(fp)) {
    fprintf(stderr, "cat: error occured on read\n");
    exit(1);
  }
}
    
    
    
