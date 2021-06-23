// Revise minprintf to handle more of the other facilities of printf

#include <stdio.h>
#include <stdarg.h>

void minprintf(char *, ...);

int main()
{
    int i = 8;
    unsigned o = 0101;
    unsigned h = 0X1A;
    unsigned u = 1U;
    char c = 'g';
    char *s = "hello";
    float f = 33.2;
    double d = 5.42312e+12;
    int *p;
    minprintf("int: %d, %i\noct: %o\nhex: %x, %X\nunsign: %u\nchar: %c\nstring: %s\n", i, i, o, h, h, u, c, s);
    minprintf("float: %f\ndouble e: %e, %E\ndouble g: %g, %G\npointer: %p\n% ", f, d, d, f, f, p);
    return 0;
}

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
    va_list ap; /* points to each unnamed arg in turn */
    char *p, *sval;
    int ival;
    unsigned uval;
    double dval;
    void *pointer;
    char localformat[100];
    char *lp = localformat;

    va_start(ap, fmt);  /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
        case 'd':                           /* handle ints */
            ival = va_arg(ap, int);
            printf("%d", ival);
            break;
        case 'i':                           /* handle ints */
            ival = va_arg(ap, int);
            printf("%i", ival);
            break;
        case 'o':                           /* handle octal */
            ival = va_arg(ap, unsigned);
            printf("%o", ival);
            break;
        case 'x':
            ival = va_arg(ap, unsigned);    /* handle hexadecimal */
            printf("%x", ival);
            break;
        case 'X':
            ival = va_arg(ap, unsigned);    /* handle hexadecimal */
            printf("%X", ival);
            break;
        case 'u':                           /* handle unsigned ints */
            uval = va_arg(ap, unsigned);
            printf("%u", uval);
            break;
        case 'c':                           /* handle char */
            ival = va_arg(ap, int);
            printf("%c", ival);
            break;
        case 's':                           /* handle strings */
            for (sval = va_arg(ap, char *); *sval; sval++)
                putchar(*sval);
            break;
        case 'f':                           /* handle floats */
            dval = va_arg(ap, double);
            printf("%f", dval);
            break;
        case 'e':                           /* Same as f but with exponent e */
            dval = va_arg(ap, double);
            printf("%e", dval);
            break;
        case 'E':                           /* Same as f but with exponent e */
            dval = va_arg(ap, double);
            printf("%e", dval);
            break;
        case 'g':                           /* to prevent trailing zeros if exponent is less than -4 or greater than equal to precision */
            dval = va_arg(ap, double);
            printf("%g", dval);
            break;
        case 'G':
            dval = va_arg(ap, double);      /* to prevent trailing zeros if exponent is less than -4 or greater than equal to precision */
            printf("%G", dval);
            break;
        case 'p':                           /* handle pointers */
            pointer = va_arg(ap, void *);
            printf("%p", pointer);
            break;
        default:
            putchar('%');
            putchar(*p);
            break;
        }
    }
    va_end(ap); /* clean up */
}