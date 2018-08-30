#include <iostream>
#include <vector>
#include <utility>

using std::vector;
using std::cout;
using std::endl;
using std::pair;

pair<int, int> FindMaximumSubarray(const vector<int>& A) {
// A[range.first : range.second - 1] will be the maximum subarray
    pair<int, int> range(0, 0);
    int min_idx = -1, min_sum = 0, sum = 0, max_sum = 0;
    for (int i = 0; i < A.size(); ++i) {
        sum += A[i];
        if (sum < min_sum) {
            min_sum = sum, min_idx = i;
        }
        if (sum - min_sum > max_sum) {
            max_sum = sum - min_sum, range = {min_idx + 1, i + 1};
        }
    }
    return range;
}

int main()
{
    vector<int> vi = {904, 40, 523, 12, -355, -385, -124, 481, -31};
    pair<int, int> ret = FindMaximumSubarray(vi);
    int sum = 0;
    for (int i = ret.first; i < ret.second; ++i) {
        sum += vi[i];
    }
    cout << "min = " << ret.first << " max = " << ret.second << " sum = " << sum << endl;
    return 0;
}

