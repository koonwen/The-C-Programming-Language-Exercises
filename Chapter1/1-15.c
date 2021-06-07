//Exercise 1-15
/* Rewrite the temperature conversion program of Section 1.2 to use a
   function for conversion */

#include <stdio.h>

double convert_C_to_F(int celsius);
double convert_F_to_C(int fahrenheit);

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
    fahr = convert_C_to_F(celsius);
    printf("%3.0f %6.1f\n", celsius, fahr);
    celsius += step;
  };
  
  return 0;
}


double convert_C_to_F(int celsius)
{
  return ((celsius * 9.0) / 5.0) + 32;
}

double convert_F_to_C(int fahrenheit)
{
  return ((fahrenheit - 32) * 5.0) / 9.0;
}
