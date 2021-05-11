// Exercise 2-10
/* Rewrite the funtion lower, which converts upper case letters to lower case, with a
    conditional expression instead of if-else */

#include <stdio.h>

void lower(char string[]);

int main()
{
    char s[] = "HELLO WORLD";
    lower(s);
    printf("%s", s);
    return 0;
}

void lower(char s[])
{
    for (int i=0; s[i] != '\0'; i++)
        s[i] += (s[i] < 'Z' && s[i] > 'A') ? ('a' - 'A') : 0;
    return;
}