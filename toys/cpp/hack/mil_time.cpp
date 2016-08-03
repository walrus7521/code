#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
    string time;
    cin >> time;
    string hr   = time.substr(0,2);
    string min  = time.substr(3,2);
    string sec  = time.substr(6,2);
    string::size_type sz;   // alias of size_t
    int hour;

    istringstream convert(hr);
    convert >> hour;

    if (time[8] == 'A') {
       ; 
    } else
    if (time[8] == 'P') {
        hour += 12;
        ostringstream convert;         
        convert << hour;
        hr = convert.str();
    }

    cout << hr << ":" << min << ":" << sec << endl;
    return 0;
}

