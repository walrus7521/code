#include <iostream>
#include <string>
#include <boost/regex.hpp>

using namespace std;

int main()
{
    string s = "who, lives:in-a,pineappl    under the sea?";
    boost::regex re(",|:|-|\\s+");
#if 0
    boost::sregex_token_iterator p(s.begin(), s.end(), re, -1);
    boost::sregex_token_iterator end;

    while (p != end)
        cout << *p++ << endl;
#endif
}
