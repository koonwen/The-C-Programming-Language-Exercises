// Sizeof values

#define f(type) printf(#type " sizeof %zu\n", sizeof(type))

#include <stdio.h>

int main()
{
  printf("Sizeof various values:\n");
  f(char);
  f(int);
  f(float);
  f(double);
  f(long);
  f(long long);
  f(size_t);
  printf("value is %d\n", '\0');
  return 0;
}


  
