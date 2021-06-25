// Exercise 8-1
/* Rewrite the program cat from Chapter 7 using read, write, open and close
   instead od their standard library equivalents. Perform experiments to
   determine the relative speeds of the two versions */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>		/* For open and close operation on files */
#include <unistd.h>		/* For read and write operation */

/* Read in file or stdin if none provided and print out to stdout */
int main(int argc, char *argv[])
{
  int fd = 0; /* default fd 0 (stdin) */
  int c;
  char buf[BUFSIZ];

  if (argc > 2) {
    printf("%s: error bad usage\n", *argv);
    exit(1);
  }
  if (*++argv != NULL)
    fd = open(*argv, O_RDONLY, 0);

  while ((c = read(fd, buf, BUFSIZ)) != 0)
    write(1, buf, c);

  if (c == EOF) {
    printf("%s: error encountered\n", *argv);
    exit(2);
  }

  close(fd);
  exit(0);
}
