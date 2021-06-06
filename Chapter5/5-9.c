// Exerrcise 5-9
/* Rewrite the routines day_of_year and month_day with pointers
   instead of indexing */

#include <stdio.h>
#include <assert.h>

int day_of_year(int, int, int);
int month_day(int, int, int *, int *);

int main()
{
  int x;
  int pmonth, pday;

  assert(day_of_year(2020, 10, 2) > 0);
  assert(day_of_year(-10, 10, 13) == -1);
  assert(day_of_year(2122, 21, 13) == -1);
  assert(day_of_year(2020, 2, 31) == -1);
  assert(day_of_year(3, 2, 29) == -1);

  assert(month_day(2020, 20, &pmonth, &pday) == 1);
  assert(month_day(2020, 3429, &pmonth, &pday) == -1);
  assert(month_day(3, 365, &pmonth, &pday) == 1);
  assert(month_day(3, 366, &pmonth, &pday) == -1);

  return 0;
}

static char daytab[2][12] = {
  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
  int leap;
  char *dp;

  if (year <= 0)		/* check valid year */
    return -1;
  if (month <= 0 || month > 12)	/* check valid month */
    return -1;

  leap = year%4 == 0 && year%100 != 0 || year %400 == 0;
  dp = daytab[leap];
  if (day <= 0 || day > dp[month-1]) /* check valid day */
    return -1;
 
  while (month--)
    day += *dp++;
  return day;
}

/* month_day: set month, day from day of year */
int month_day(int year, int yearday, int *pmonth, int *pday)
{
  int leap;
  char *p, *start;
  
  if (year <= 0)		/* check valid year */
    return -1;

  leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
  int maxdays = leap ? 366 : 365;
  if (yearday <= 0 || yearday > maxdays) /* check valid yearday */
    return -1;

  start = daytab[leap];
  p = start;
  while(yearday > *p)
    yearday -= *p++;
  *pmonth = p - start;
  *pday = yearday;
  return 1;
}
