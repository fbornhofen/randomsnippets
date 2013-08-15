#include <stdio.h>

const int k_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int is_leap(int yr)
{
    return yr % 4 == 0 && (yr % 100 != 0 || yr % 400 == 0);
}

int days(int yr, int mo)
{
    if (mo == 1) {
        return is_leap(yr) ? 29 : 28;
    }
    return k_days[mo];
}

int main()
{
    int sundays_on_first = 0;
    int weekday = 1; /* Monday, 1900-01-01 */
    int year = 1900;
    int month = 0;
    int mdays = 0;
    while (year < 2001) {
        if (weekday == 0 && year > 1900) {
            ++sundays_on_first;
        }
        mdays = days(year, month);
        if (month == 11) {
            month = 0;
            ++year;
        } else {
            ++month;
        }
        weekday = (weekday + mdays) % 7;
    }

    printf("%d\n", sundays_on_first);
    return 0;
}


