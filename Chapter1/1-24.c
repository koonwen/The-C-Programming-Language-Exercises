//Exercise 1-24
//Write a program to check a C program for rudimentary syntax errors like unbalanced parentheses, brackets and braces. Don't forget about quotes, both single and double, escape sequences, and comments. (This program is hard if you do it in full generality)


#include <stdio.h>

#define STACKSIZE 100

void ignore(char c);
char pop();
char peek();
void push(char paran);
int paran_match(char p1, char p2);

char stack[STACKSIZE];
int top = 0;

int main()
{
  int c;
  
  while ((c = getchar()) != EOF) {

    if (c == '\'' || c == '\"' || c == '\\')
      ignore(c);
    
    if (c == '(' || c == '[' || c == '{')
      push(c);
    else if (c == ')' || c == ']' || c == '}') {
      if (paran_match(peek(), c)){
	if (pop() == 0) {
	  printf("\nParantheses matching error");
	  return 0;
	}
      }
      else {
	printf("\nParantheses matching error");
	return 0;
      }
    }
  }


  if (stack[0] == 0)
    printf("\nProgram compiled without errors!");
  else
    printf("\nParantheses matching error");   

  return 0;
}


char pop()
{
  if (top == 0) {
    printf("Stack is already empty!");
    return 0;
  }
      
  char c = stack[--top];
  stack[top] = 0;
  return c;
}

char peek()
{
  if (top == 0) {
    printf("Stack is already empty!");
    return 0;
  }
  return stack[top-1];
}

void push(char p)
{
  stack[top++] = p;
}


int paran_match(char p1, char p2)
{
  if (p1 == '(' && p2 == ')')
    return 1;

  if (p1 == '[' && p2 == ']')
    return 1;

  if (p1 == '{' && p2 == '}')
    return 1;

  return 0;
}
    
void ignore(char c)
{
  if (c == '\'') {
    while ((c = getchar()) != EOF && c != '\''){
      if (c == '\\')
        c = getchar();
    };
    return;
  }

  if (c == '\"') {
    while ((c = getchar()) != EOF && c != '\"'){
      if (c == '\\')
	c = getchar();
    };
    return;
  }
  
  if (c == '\\') {
    c = getchar();
    c = getchar();
    return;
  }
  
  return;
}
