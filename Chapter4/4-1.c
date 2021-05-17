// Exercise 4-1
/* Write the function strrindex(s,t), which returns the position of the rightmost
    occurence of t in s, or -1 if there is none.
*/

#include <stdio.h>

int strrindex(char source[], char searchfor[]);

char searchfor[] = "complete";
char source[] = "If not you won't give it your best shot!";
char gotocase[] = "com";

int main(){
    printf("search returned: %d index\n", strrindex(gotocase, searchfor));
    return 0;
}

int strrindex(char s[], char t[]) {
    int i, j, k;
    int hold = -1;

    for(i=0; s[i] != '\0'; i++)
        for (j=i, k=0; t[k]==s[j];) {
            if (t[++k] == '\0')
                hold = i;
            if (s[++j] == '\0')
                goto finish;
        }

    finish:
    if (hold > 0)
        return hold;
    else
        return -1;
}