#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

using namespace std;

/*
 * Midnight is 12:00:00AM on 12-hour clock, and 00:00:00 on a 24-hour clock.
 * Noon is 12:00:00PM on a 12-hour clock, and 12:00:00 on a 24-hour clock.
 *
 * Convert from 12-hour format to 24-hour format, 
 *      where format is hh:mm:ssAM/PM
 *      01 <= hh <= 12 12-hour time.
 *
 * Convert to 
 *      01 <= hh <= 23 24-hour time.
 *
 */
int main()
{
    string time;
    cin >> time;
    string hr   = time.substr(0,2);
    string min  = time.substr(3,2);
    string sec  = time.substr(6,2);
    string::size_type sz;
    int hour;

    istringstream convert(hr);
    convert >> hour;

    if (time[8] == 'A') {
       ; 
       if (hr == "12") {
           hr = "00";
       }
    } else
    if (time[8] == 'P') {
       if (hr == "12") {
           hr = "12";
       } else {       
            hour += 12;
            ostringstream convert;         
            convert << hour;
            hr = convert.str();
       }
    }

    cout << hr << ":" << min << ":" << sec << endl;
    return 0;
}

