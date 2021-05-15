// Exercise 3-3
/* Write a function expand(s1, s2) that expands shorthand notation like a-z in the string s1 into the equivalent complete
    list abc..xyz in s2. ALlow for letters of either case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z.
    Arrange that a leading or trailing - is taken literally.
*/

#include <stdio.h>
#include <string.h>
#define BUFFERSIZE 1000

void expand(char s1[], char s2[]);

int main()
{
    char s1[] = "hea-zllo m-n -abs5";
    char s2[BUFFERSIZE];
    expand(s1, s2);
    printf("%s", s2);
    return 0;
}

void expand(char s1[], char s2[])
{
    int i, j;
    for (i=j=0; s1[i] != '\0' && i < BUFFERSIZE-1; i++, j++) {
        if (s1[i] != '\t' || s1[i] != '\n'|| s1[i] != ' ')
            if (s1[i+1] == '-')
                if (s1[i+2] != '\t' || s1[i+2] != '\n'|| s1[i+2] != ' ' || s1[i+2] != '\0') {
                    for (int tmp=s1[i]; tmp<=s1[i+2]; tmp+=1)
                        s2[j++] = tmp;
                    i += 3;
                }
        s2[j] = s1[i];
    }
}