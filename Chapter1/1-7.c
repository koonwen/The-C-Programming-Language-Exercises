//Excercise 1-7
//Write a program to print the value of EOF

#include <stdio.h>

int main()
{
  printf("The value of EOF is %d\n", EOF); // Notice that you cannot use %c because it is not big enough to hold EOF
  printf("Trying to use %%c we get %c\n", EOF);

  return 0;
}

//Value of EOF is -1
