// Exercise 7-6
/* Write a program to compare two files, printing the first line
   where they differ */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100

int diff(FILE *, FILE *);

int main(int argc, char *argv[])
{
  if (argc != 3) {
    printf("Usage: file1 file2\n");
    exit(0);
  }
  FILE *fp1, *fp2;
  fp1 = fopen(argv[1], "r");
  fp2 = fopen(argv[2], "r");

  if (fp1 == NULL || fp2 == NULL) {
    printf("error opening files\n");
    exit(1);
  }
    
  if (diff(fp1, fp2) != 0)
    exit(2);

  fclose(fp1);
  fclose(fp2);
  exit(0);
}
  
    

int diff(FILE *fp1, FILE *fp2)
{
  char line1[MAXLINE], line2[MAXLINE];
  char *s, *t;
  
  while (fgets(line1, MAXLINE, fp1) != NULL && fgets(line2, MAXLINE, fp2) != NULL) {
    s = line1;
    t = line2;
    while (*s++ == *t++)
      ;
    if (*s == '\0' || *t == '\0')
      continue;
    else {
      printf(">%s<%s", line1, line2);
      return 0;
    }
  }
  if (*s == '\0' || *t == '\0')
    return 0;
  exit(1);
}
	       
  
