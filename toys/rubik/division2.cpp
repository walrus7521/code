#include <cstdio>
#include <set>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

void divide()
{
    int N;
    int abcde, fghij;

    set<int> num;
    set<int> den;
    vector<pair<int, int>> answer;
    vector<int> intersection;

    int x, save_x;
    for (N = 2; N <= 79; N++) {

        for (int start = 98765; start >= 1234; start--) {

            fghij = start;
            x = fghij * N;
            save_x = x;

            if (x > 98765 || x < 1234) {
                continue;
            }

            intersection.clear();
            num.clear();
            den.clear();
        
            //printf("x: %d = %d x %d\n", x, fghij, N);
            for (int i = 0; i < 5; i++) {
                den.insert(fghij % 10);            
                fghij /= 10;
                num.insert(x % 10);            
                x /= 10;
            }
            // if both sets have 5 items
            if (num.size() < 5 || den.size() < 5) {
                continue;
            }
            // if sets are unique
            set_intersection(num.begin(), num.end(), den.begin(), den.end(), std::inserter(intersection, intersection.begin()));
            // 
            // create pair save_x and start and add to answer vector
            if (!intersection.size()) {
                answer.push_back(make_pair(save_x, start));
            }
        }

    }

    for (auto it = answer.begin() ; it != answer.end(); ++it) {
        printf("%05d, %05d\n", it->first, it->second);
    }

}

int main()
{
    divide();
}

