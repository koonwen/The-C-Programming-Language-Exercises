// Exercise 2-9
/* In a two's complement number syste,, x &= (x=1) deletes the rightmost 1-bit in x.
    Explain why. Use this observation to write a faster version of bitcount. */

/* Ans: The difference between the binary form of x and x-1 is the complement until the first 1 bit. E.g.
    x = 100100 and x-1 = 100011. Therefore the & operation between x and x-1 will only delete the rightmost 
    bit */

#include <stdio.h>
#include <assert.h>

int bitcount(unsigned x);

int main()
{
    int x = 68;
    int expected_count = 2;
    int result = bitcount(x);
    assert(expected_count == result);
    printf("%d", result);
    return 0;
}

int bitcount(unsigned x)
{
    int cnt;
    for (cnt = 0; x; cnt++)
        x &= x - 1;
    return cnt;
}
