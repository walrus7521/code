#include <cstdio>
#include <ctime>

#define PAGES_PER_DAY 4
#define NUM_DAYS 88

// Adjust date by a number of days +/-
void DatePlusDays( struct tm* date, int days )
{
    const time_t ONE_DAY = 24 * 60 * 60 ;

    // Seconds since start of epoch
    time_t date_seconds = mktime( date ) + (days * ONE_DAY) ;

    // Update caller's date
    // Use localtime because mktime converts to UTC so may change date
    *date = *localtime( &date_seconds );
}

//typedef enum week {
//    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
//} week_day;

int next(int day, int page)
{
    time_t t = time(NULL);
    struct tm *date = localtime(&t);
    char buffer [80];
    //printf("%s\n", asctime(date));

    DatePlusDays(date, day);
    strftime (buffer,80,"%a (%m/%d)", date);
    //printf("date: %s\n", buffer);
    printf("[  ] %s :=> pgs [%03d - %03d]\n", 
            buffer, page, page + PAGES_PER_DAY);
    return page + PAGES_PER_DAY;
}

int main()
{
    int page = 516;
    int i;

    printf("Study schedule for C++\n\n");

    for (i = 1; i <= NUM_DAYS; i++) {
        page = next(i, page);
    }

}
