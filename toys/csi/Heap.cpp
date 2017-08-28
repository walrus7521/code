#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <functional>

using namespace std;

// return the k longest strings
vector<string> TopK(int k, istringstream* stream)
{
    priority_queue<string, vector<string>, function<bool(string, string)>>
        min_heap(
            [](const string& a, const string& b) { 
                return a.size() >= b.size(); });

    string next_string;
    while (*stream >> next_string) {
        min_heap.emplace(next_string);
        if (min_heap.size() > k) {
            // remove shortest string, compare function above
            // orders strings by length
            min_heap.pop();
        }
    }

    vector<string> result;
    while (!min_heap.empty()) {
        result.emplace_back(min_heap.top());
        min_heap.pop();
    }

    return result;
}

int main () {

    string stringvalues = "blue red yellow magenta";
    istringstream iss (stringvalues);

    vector<string> top = TopK(2, &iss);
    for (auto& t : top) {
        cout << t << endl;
    }

  return 0;
}
