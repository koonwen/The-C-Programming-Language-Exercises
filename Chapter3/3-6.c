// Exercise 3-6
/* Write a version of itoa that accepts three arguements instead
    of two. The third arguement is a minimum field width; the 
    converted number must be padded with blanks on the left if
    neccessay to make it wide enough
*/
#include <stdio.h>
#include <string.h>
#include <limits.h>

void itoa(int width, int n, char s[]);
void reverse(char s[]);

int main()
{
    char s[20];
    int width = 10;
    int n = 500;
    
    itoa(width, n, s);
    printf("%s\n", s);

    return 0;
}

void itoa(int width, int n, char s[])
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

    if ((width = width - i) > 0)
        while (width)
            s[i++] = ' ', width--;
    
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