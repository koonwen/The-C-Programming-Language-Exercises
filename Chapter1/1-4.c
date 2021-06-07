//Exercise 1-4
/* Write a program to print the corresponding Celsius to Fahrenheit
   table */

#include <stdio.h>

int main()
{
  float celsius, fahr;
  int upper, lower, step;

  lower = 0;
  upper = 300;
  step = 20;

  char c = 'C';
  char f = 'F';
  printf("%3c %6c\n", c, f);
  celsius = lower;
  while (celsius <= 300) {
    fahr = ((celsius * 9.0) / 5.0) + 32;
    printf("%3.0f %6.1f\n", celsius, fahr);
    celsius += step;
  };
  
  return 0;
}
