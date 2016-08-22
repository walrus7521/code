#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <regex>

using namespace std;


int main(){

    std::regex gmail(".*@gmail.*", std::regex_constants::ECMAScript | std::regex_constants::icase);
    int N;
    vector<pair<string, string> > items;
    cin >> N;
    for(int a0 = 0; a0 < N; a0++){
        string firstName;
        string emailID;
        cin >> firstName >> emailID;

        if (regex_match(emailID, gmail)) {
            items.push_back(make_pair(firstName, emailID));
        }
    }

    std::sort(items.begin(), items.end());

    for (vector<pair<string,string> >::iterator it=items.begin(); it!=items.end(); ++it) {
        std::cout << it->first << endl;
    }

    return 0;
}

