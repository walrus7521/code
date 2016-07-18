#include <iostream>
#include <vector>
#include <utility>

using namespace std;
/*
   Given an array A of length n whose entries are integers, compute
   the largest product that can be made using n-1 entries in A.  You
   cannot use an entry more than once.  Array entries may be positive
   negative or zero.  Your algorithm cannot use the division operator,
   explicitly or implicitly.
 */

pair<int, int> LargestProduct(vector<int> A)
{
    pair<int, int> answer;
    int product = 1;
    int max_product, max_product_skip_index;
    for (int i = 0; i < A.size(); ++i) {
        product = 1;
        for (int j = 0; j < A.size(); ++j) {
            if (j == i) continue;
            product *= A[j];
        }
        if (product > max_product) {
            max_product = product;
            max_product_skip_index = i;
        }
    }
    answer.first = max_product;
    answer.second = max_product_skip_index;
    return answer;
}

int main()
{
    // A = <3,2,5,4> = <3,5,4> = 60
    // A = <3,2,-1,4> = <3,2,4> = 24
    // A = <3,2,-1,4,-1,6> = <3,-1,4,-1,6> = 72
    int array[] = {3, 2, -1, 4, -1, 6};
    //int array[] = {3, 2, -1, 4};
    //int array[] = {3, 2, 5, 4};
    vector<int> A (array, array + sizeof(array)/sizeof(array[0]));
    pair<int, int> x = LargestProduct(A);
    cout << "largest product: " << x.first << " -> skip A[" << x.second << "] = " << A[x.second] << endl;

}
