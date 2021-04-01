//Exercise 1-6.
// Verify that the expression getchar() != EOF is 0 or 1

#include <stdio.h>

int main()
{
  printf("%d", getchar() != EOF);
  
  return 0;
}

//The check != returns 1 for true and 0 for false.
