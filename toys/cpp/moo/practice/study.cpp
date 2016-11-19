#include <cstdio>
#include <ctime>

#define PAGES_PER_DAY 5

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


int next(int day, int page)
{
    time_t t = time(NULL);
    struct tm *date = localtime(&t);
    //printf("%s\n", asctime(date));

    DatePlusDays(date, day);
    printf("[  ] [%02d] :/ [%02d:%02d] pgs [%03d - %03d]\n", 
            day, date->tm_mon+1, date->tm_mday, page, page + PAGES_PER_DAY);
    return page + PAGES_PER_DAY;
}

int main()
{
    int page = 516;
    int i;

    printf("Study schedule for C++\n\n");

    for (i = 1; i <= 70; i++) {
        page = next(i, page);
    }

}
