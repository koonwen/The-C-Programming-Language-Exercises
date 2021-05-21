// Exercise 4-2
/* Extend atof to handle scientific notation of the form 
    123.45e-6
    where a floating-point number may be followed by e 
    or E and an optionally signed exponent
*/

#include <ctype.h>
#include <stdio.h>
#include <math.h>

double atof(char s[]);
double pow(double val, double multiplier);

int main() {
    char s[] = "123.45e-6";
    printf("%f\n", atof(s));
    double s1 = 0.00012345;
    printf("%f\n", s1);
    return 0;
}

/* extended atof: convert string s to double including scientific notation */
double atof(char s[])
{
    double val, power;
    int i, sign;
    int sci_sign, multiplier;

    for (i=0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
    }
    if (s[i] == '.')
        i++;
    for (power=1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    double tmp = sign * val / power;

    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        sci_sign = (s[i++] == '-') ? -1 : 1;
        for (multiplier=0.0; s[i]!='\0'; i++) {
            multiplier =  multiplier * 10.0 + (s[i] - '0');
        }
        switch (sci_sign) {
            case 1:
                return tmp * pow(10.0, multiplier);
            case -1:
                return tmp * pow(10.0, -multiplier);
        }
    }

    return tmp;
}