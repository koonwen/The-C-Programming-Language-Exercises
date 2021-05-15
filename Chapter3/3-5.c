/// Exercise 3-5
/* Write the function itob(n, s, b) that converts the integer n into a base
    b character representation in the string s. In particular, itob(n, s, 16)
    formats n as a hexadecimal integer in s
*/

#include <stdio.h>
#include <string.h>

void itob(int n, char s[], int b);
void reverse(char s[]);

int main()
{
    int n = 500;
    char s[20];
    itob(n, s, 16);
    printf("%s\n", s);
    return 0;
}

void itob(int n, char s[], int b) {

    int i, tmp, sign;
    i = 0;

    if ((sign = n) < 0)
        n = -n;

    do {
        tmp = n % b;
        s[i++] = tmp <= 9 ? (tmp + '0') : (tmp - 10 + 'a');
    } while ((n /= b) > 0);

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