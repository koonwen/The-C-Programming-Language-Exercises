//Exercise 1-11
//How would you test the word count program? What kinds of input are the most likely to uncover bugs if there are any?


//Word count program given in the book
#include <stdio.h>

#define IN 1    /* inside a word */
#define OUT 0   /* outside a word */

/* count lines, words, and characters in input */
int main()
{
  int c, nl, nw, nc, state;
  
  state = OUT;
  nl = nw = nc = 0;
  while ((c = getchar()) != EOF) {
    ++nc;
    if (c == '\n')
      ++nl;
    if (c == ' ' || c == '\n' || c == '\t')
      state = OUT;
    else if (state == OUT) {
      state = IN;
      ++nw;
    }    
  }
  printf("%d %d %d\n", nl, nw, nc);
    
  return 0;
}


//ANS: Create a test function to randomly generate input with many spaces between words, tabs and newlines are mainly used in this function to count words.
