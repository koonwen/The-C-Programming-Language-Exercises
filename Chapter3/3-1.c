// Exercise 3-1
/* Our binary search makes two tests inside the loop, when one would suffice 
(at the price of more tests outside). Write a version with only one test inside
the loop and measure the time difference */

#include <stdio.h>
#include <assert.h>
#include <time.h>

int binsearch(int x, int v[], int n);
int mybinsearch(int x, int v[], int n);

int main() 
{
    int x = 3;
    int v[] = {1,23,45,78,100,102};
    int n = 6;

    time_t start, first_end, second_end; 

    time(&start);
    binsearch(x, v, n);
    time(&first_end);
    mybinsearch(x, v, n);
    time(&second_end);
    assert(binsearch(x, v, n) == mybinsearch(x, v, n));
    printf("binsearch took: %f\n", difftime(start, first_end));
    printf("mybinsearch took: %f\n", difftime(first_end, second_end));
    return 0;
}

int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n-1;
    while (low <= high) {
        mid = (low+high)/2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;         /* found match */
    }
    return -1;                  /* no match */
}

int mybinsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n-1;
    mid = (low+high)/2;
    while (v[mid] != x && low <= high) {
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
        mid = (low+high)/2;
    }
    if (v[mid] == x)
        return mid;
    else
        return -1;
}