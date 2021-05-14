// Exercise 3-2
/* Write a function escapr(s,t) that converts characters like newline and tab into visible escape
    sequences like \n and \t as it copies the string t to s. Use a switch. Write a function for the
    other direction as well, converting escape sequences into the real characters.
*/

#include <stdio.h>

#define BUFFERSIZE 100

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

int main()
{
    char t[] = "this is \n a test \t string";
    char s[BUFFERSIZE];
    escape(s, t);
    printf("after escape: %s\n", s);
    unescape(t, s);
    printf("after unescape: %s\n", t);
    return 0;
}

void escape(char s[], char t[])
{
    int c, i, j;
    for (int i = j = 0; (c = t[i]) != '\0'; i++)
        switch (c) {
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
            default:
                s[j++] = c;
        }
    return;
}

void unescape(char s[], char t[])
{
    int c, i, j, k;
    for (int i = j = 0; (c = t[i]) != '\0'; i++)
        if (c == '\\') {
            switch (k = t[i+1]) {
                case 'n':
                    s[j++] = '\n';
                    i++;
                    break;
                case 't':
                    s[j++] = '\t';
                    i++;
                    break;
                default:
                    s[j++] = c;
                    s[j++] = k;
                    break;
            }
        } else {
            s[j++] = c;
        }
    return;
}