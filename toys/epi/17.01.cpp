#include <iostream>
#include <vector>
#include <utility>

/**
 * Count the number of score combinations for football:
 *   given score s find combinations of W[]'s
 *   for example, s = 12, and W is
 *       W[0] =  safety     = 2
 *       W[1] =  field goal = 3
 *       W[2] =  touchdown  = 7
 *   can make the sum s.
 *   6 safeties = 2x6 = 12
 *   4 field goals = 2x6 = 12
 *   3 safeties and 2 field goals = 2x3 + 3x2= 12
 *   1 safety, 1 field goal, and 1 touchdown = 2x1 + 3x1 + 7x1 = 12
 */

using std::vector;
using std::cout;
using std::endl;
using std::pair;

vector<int> CountCombinations(int k, const vector<int>& score_ways) {
    vector<int> combinations(k + 1, 0);
    combinations[0] = 1; // 1 way to reach 0
    for (const int& score : score_ways) {
        for (int j = score; j <= k; ++j) {
            combinations[j] += combinations[j - score];
        }
    }
    return combinations;
}

vector<int> CountPermutations(int k, const vector<int>& score_ways) {
    vector<int> permutations(k + 1, 0);
    permutations[0] = 1; // 1 way to reach 0
    for (int i = 0; i <= k; ++i) {
        for (const int& score : score_ways) {
            if (i >= score) {
                permutations[i] += permutations[i - score];
            }
        }
    }
    return permutations;
}

/**
 * Strategy: 
 *  compute all pairs [div, mod] => [ s div W[i], s mod W[i] ]
 *
 */

vector<pair<int, int>> ComputePairs(const vector<int>& W, int s) {
// A[range.first : range.second - 1] will be the maximum subarray
    vector<pair<int, int>> div_mods;
    pair<int, int> div_mod;
    int min_idx = -1, min_sum = 0, sum = 0, max_sum = 0;
    int div, mod;
    for (int i = 0; i < W.size(); ++i) {
        div = s / W[i];
        mod = s % W[i];
        div_mod = {div, mod};
        div_mods.push_back(div_mod);
    }
    return div_mods;
}

int main()
{
    vector<int> ways = {2, 3, 7};
    int sum = 12;
    vector<pair<int, int>> ret1 = ComputePairs(ways, sum);
    vector<int> ret2 = CountCombinations(sum, ways);
    vector<int> ret3 = CountPermutations(sum, ways);
    cout << endl << "compute combinations of {";
    for (const int i : ways) {
        cout << i << ", ";
    }
    cout << "} ";
    cout << "that sum to " << sum << endl << endl;
    for (const pair<int,int> pi : ret1) {
        cout << "pairs = [div:" << pi.first << ", mod:" << pi.second << "]" << endl;
    }
    cout << endl;
    cout << "combos" << endl;
    int reach_sum = 0;
    for (const int i : ret2) {
        cout << i << " ways to reach " << reach_sum++ << endl;
    }
    cout << endl;
    cout << "permutations" << endl;
    reach_sum = 0;
    for (const int i : ret3) {
        cout << i << " ways to reach " << reach_sum++ << endl;
    }
    cout << endl;
    return 0;
}

/**
    compute combinations of {2, 3, 7, } that sum to 12

    pairs = [div:6, mod:0]
    pairs = [div:4, mod:0]
    pairs = [div:1, mod:5]

    combos = 1
    combos = 0
    combos = 1
    combos = 1
    combos = 1
    combos = 1
    combos = 2
    combos = 2
    combos = 2
    combos = 3
    combos = 3
    combos = 3
    combos = 4

    perms = 1
    perms = 0
    perms = 1
    perms = 1
    perms = 1
    perms = 2
    perms = 2
    perms = 4
    perms = 4
    perms = 7
    perms = 9
    perms = 12
    perms = 18

**/
