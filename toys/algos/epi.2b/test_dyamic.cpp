#include <iostream>
#include <string>

#include "Dynamic.hpp"

// Driver program
int main()
{
    // your code goes here
    string str1 = "sunday";
    string str2 = "saturday";
 
    cout << "NP: " << editDist(str1, str2, str1.length(), str2.length()) << endl;
    cout << "DP: " << editDistDP(str1, str2, str1.length(), str2.length()) << endl;
 
    return 0;
}
