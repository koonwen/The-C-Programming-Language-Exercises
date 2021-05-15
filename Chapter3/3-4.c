// Exercise 3-4
/* In a two's a complement number representation, our version of itoa does not handle the largest
    negative number, that is, the value of n equal to -(2^wordsize-1). Explain why not. Modify it
    to print that value correctly regardless of the machine on which it runs. 
*/

/* Ans: Since the largest negative number represented in binary in the twos a complement system is
    equivalent to all the bits turned on, e.g for an 8 bit system 1 1 1 1 1 1 1 1, hence the itoa 
    function described in the book will be unable to convert this number to a positve value. The 
    way I propose to solve this is to provide an outer test to check if the word is equivalent to
    the largest negative number, if so then it returns the largest negative number based on the systems
    architecture. */

#include <stdio.h>
#include <limits.h>
#include <string.h>

void myitoa(int n, char s[]);
void reverse(char s[]);

int main()
{
    int n = 500;
    int largest_negative = INT_MIN;
    char s[20];

    myitoa(n, s);
    printf("%s\n", s);
    
    myitoa(largest_negative, s);
    printf("%s\n", s);

    return 0;
}

void myitoa(int n, char s[])
{
    int i, sign;

    i = 0;
    if ((sign = n) < 0) {
        if (n == INT_MIN) {
            n = INT_MAX;
            s[i++] = n % 10 + '0' + 1;
        }
        else
            n = -n;    
    }

    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])
{
    int back = strlen(s) - 1;
    int tmp;
    for(int start=0; start<back; back--, start++)
        tmp=s[start], s[start]=s[back], s[back]=tmp;
}